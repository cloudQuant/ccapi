#include <gtest/gtest.h>
#include <boost/system/error_code.hpp>
#include <zlib.h>
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include "ccapi_cpp/ccapi_logger.h"
#include "ccapi_cpp/ccapi_inflate_stream.h"

std::vector<uint8_t> gzipCompress(const std::string& input) {
  z_stream zs;
  memset(&zs, 0, sizeof(zs));

  if (deflateInit2(&zs, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 31, 8, Z_DEFAULT_STRATEGY) != Z_OK) {
    throw(std::runtime_error("deflateInit2 failed while compressing."));
  }

  zs.next_in = (Bytef*)input.data();
  zs.avail_in = input.size();

  int ret;
  std::vector<uint8_t> outbuffer;
  outbuffer.resize(32768);

  do {
    zs.next_out = reinterpret_cast<Bytef*>(outbuffer.data());
    zs.avail_out = outbuffer.size();

    ret = deflate(&zs, Z_FINISH);

    if (outbuffer.size() - zs.avail_out > 0) {
      outbuffer.resize(outbuffer.size() - zs.avail_out);
    }
  } while (ret == Z_OK);

  deflateEnd(&zs);

  if (ret != Z_STREAM_END) {
    throw(std::runtime_error("Exception during zlib compression: (" + std::to_string(ret) + ") " + zs.msg));
  }

  return outbuffer;
}

using namespace ccapi;

TEST(InflateStreamTest, DecompressValidData) {
  // 创建 InflateStream 实例
  ccapi::InflateStream inflateStream;

  // 设置 windowBitsOverride 以支持 GZIP 格式
  inflateStream.setWindowBitsOverride(31);

  // 初始化 InflateStream
  boost::system::error_code ec = inflateStream.init();
  EXPECT_EQ(ec, boost::system::error_code()) << "InflateStream initialization failed!";

  // 准备测试数据（gzip 压缩字符串 "Hello, World!"）
  const uint8_t compressedData[] = {
      0x1f, 0x8b, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x13,
      0xf3, 0x48, 0xcd, 0xc9, 0xc9, 0xd7, 0x51, 0x08, 0xcf,0x2f,
      0xca, 0x49, 0x51, 0x04, 0x00, 0xd0, 0xc3, 0x4a, 0xec,0x0d,
      0x00, 0x00,0x00
  };
  size_t compressedSize = sizeof(compressedData);
  std::string decompressedOutput;

  // 解压缩数据
  ec = inflateStream.decompress(compressedData, compressedSize, decompressedOutput);
  EXPECT_EQ(ec, boost::system::error_code()) << "Decompression failed!";

  // 输出解压后的内容，帮助调试
  std::cout << "Decompressed output: " << decompressedOutput << std::endl;

  // 验证解压缩结果
  EXPECT_EQ(decompressedOutput, "Hello, World!") << "Decompressed output does not match the expected result!";
}

TEST(InflateStreamTest, DecompressInvalidData) {
  // 创建 InflateStream 实例
  ccapi::InflateStream inflateStream;

  // 设置 windowBitsOverride 以支持 GZIP 格式
  inflateStream.setWindowBitsOverride(31);

  // 初始化 InflateStream
  boost::system::error_code ec = inflateStream.init();
  EXPECT_EQ(ec, boost::system::error_code()) << "InflateStream initialization failed!";

  // 准备无效的测试数据（故意损坏的 gzip 数据）
  const uint8_t invalidCompressedData[] = {
      0x1f, 0x8b, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf3, 0x48,
      0xcd, 0xc9, 0xc9, 0x57, 0x08, 0xcf, 0x2f, 0xca, 0x49, 0x01, 0x00, 0x85,
      0x11, 0x4a, 0x0d, 0x0c, 0x00, 0x00, 0x00, 0xff, 0xff
  };
  size_t invalidCompressedSize = sizeof(invalidCompressedData);
  std::string decompressedOutput;

  // 解压缩数据
  ec = inflateStream.decompress(invalidCompressedData, invalidCompressedSize, decompressedOutput);
  EXPECT_NE(ec, boost::system::error_code()) << "Decompression should fail with invalid data!";

  // 验证解压缩结果为空
  EXPECT_EQ(decompressedOutput, "") << "Decompressed output should be empty for invalid data!";
}

TEST(InflateStreamTest, DecompressUninitialized) {
  // 创建未初始化的 InflateStream 实例
  ccapi::InflateStream inflateStream;

  // 准备测试数据（gzip 压缩字符串 "Hello, World!"）
  const uint8_t compressedData[] = {
      0x1f, 0x8b, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf3, 0x48,
      0xcd, 0xc9, 0xc9, 0x57, 0x08, 0xcf, 0x2f, 0xca, 0x49, 0x01, 0x00, 0x85,
      0x11, 0x4a, 0x0d, 0x0c, 0x00, 0x00, 0x00
  };
  size_t compressedSize = sizeof(compressedData);
  std::string decompressedOutput;

  // 解压缩数据（未初始化）
  boost::system::error_code ec = inflateStream.decompress(compressedData, compressedSize, decompressedOutput);
  EXPECT_NE(ec, boost::system::error_code()) << "Decompression should fail when not initialized!";

  // 验证解压缩结果为空
  EXPECT_EQ(decompressedOutput, "") << "Decompressed output should be empty when not initialized!";
}



// 测试默认构造函数和初始状态
TEST(InflateStreamTest, DefaultConstructorInitializesMembers) {
  InflateStream inflateStream;

  // 验证成员变量的默认值
  EXPECT_EQ(inflateStream.toString(), "InflateStream [windowBits = 15]");
}

// 测试设置 windowBitsOverride
TEST(InflateStreamTest, SetWindowBitsOverride) {
  InflateStream inflateStream;

  // 设置 windowBitsOverride
  inflateStream.setWindowBitsOverride(31);

  // 初始化 InflateStream 并检查是否正常初始化
  boost::system::error_code ec = inflateStream.init();
  EXPECT_FALSE(ec);  // 检查是否无错误
}

// 测试重置解压缩流
TEST(InflateStreamTest, InflateReset) {
  InflateStream inflateStream;
  EXPECT_FALSE(inflateStream.init());

  // 重置解压缩流
  boost::system::error_code ec = inflateStream.inflate_reset();
  EXPECT_FALSE(ec);  // 检查重置是否无错误
}
