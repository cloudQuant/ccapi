#include "ccapi_cpp/ccapi_session.h"
namespace ccapi {
Logger* Logger::logger = nullptr;  // This line is needed.

class MyEventHandler : public EventHandler {
 public:
  void save_binance_depth_data(Message & msg){
    std::string symbol_id = msg.getSymbolId();
    std::string server_time = msg.getTimeISO();
    std::string local_update_time = msg.getTimeReceivedISO();
    std::vector<Element> elements = msg.getElementList();
    std::vector<double> ask_price_list;
    std::vector<double> bid_price_list;
    std::vector<double> ask_volume_list;
    std::vector<double> bid_volume_list;
    for (auto & element : elements){
      if (element.has("BID_PRICE")){
        bid_price_list.push_back(std::stod(element.getValue("BID_PRICE")));
        bid_volume_list.push_back(std::stod(element.getValue("BID_SIZE")));
      }
      if (element.has("ASK_PRICE")){
        ask_price_list.push_back(std::stod(element.getValue("ASK_PRICE")));
        ask_volume_list.push_back(std::stod(element.getValue("ASK_SIZE")));
      }
    }
    std::cout << symbol_id << " " << server_time << " " << local_update_time << std::endl;
    std::cout << "[ ";
    for (auto & d : ask_price_list){
      std::cout << d << " ";
    }
    std::cout << "]" << std::endl;
  }

  void save_binance_agg_trade_data(Message & msg){
    std::string symbol_id = msg.getSymbolId();
    std::string server_time = msg.getTimeISO();
    std::string local_update_time = msg.getTimeReceivedISO();
    // {AGG_TRADE_ID=1889900445, IS_BUYER_MAKER=1, LAST_PRICE=3686.73, LAST_SIZE=0.012}
    std::cout <<"agg_trade " <<  symbol_id << " " << server_time << " " << local_update_time << std::endl;
  }
  bool processEvent(const Event& event, Session* session) override {
    // std::cout << toString(event) + "\n" << std::endl;
    std::vector<Message> msgs = event.getMessageList();
    Message msg = msgs[0];
    // 如果订阅的是
    if (msg.getType() == Message::Type::MARKET_DATA_EVENTS_MARKET_DEPTH){
      save_binance_depth_data(msg);
    }
    // 如果是归集交易(agg_trade)
    if (msg.getType() == Message::Type::MARKET_DATA_EVENTS_AGG_TRADE){
      save_binance_agg_trade_data(msg);
      std::cout << toString(event) + "\n" << std::endl;
    }
    if (msg.getType() == Message::Type::MARKET_DATA_EVENTS_MARK_PRICE){
      std::cout << toString(event) + "\n" << std::endl;
    }

    return true;
  }
};
} /* namespace ccapi */
using ::ccapi::Event;
using ::ccapi::EventDispatcher;
using ::ccapi::MyEventHandler;
using ::ccapi::Session;
using ::ccapi::SessionConfigs;
using ::ccapi::SessionOptions;
using ::ccapi::Subscription;
using ::ccapi::toString;
int main(int argc, char** argv) {
  // std::cout << "CCAPI_EXCHANGE_NAME_BINANCE_USDS_FUTURES = " << CCAPI_EXCHANGE_NAME_BINANCE_USDS_FUTURES << std::endl;
  std::vector<std::string> modeList = {
      "dispatch_events_to_multiple_threads",
      "handle_events_in_batching_mode",
  };
  if (argc != 2 || std::find(modeList.begin(), modeList.end(), argv[1]) == modeList.end()) {
    std::cerr << "Please provide one command line argument from this list: " + toString(modeList) << std::endl;
    return EXIT_FAILURE;
  }
  std::string mode(argv[1]);
  if (mode == "dispatch_events_to_multiple_threads") {
    SessionOptions sessionOptions;
    SessionConfigs sessionConfigs;
    MyEventHandler eventHandler;
    EventDispatcher eventDispatcher(2);
    Session session(sessionOptions, sessionConfigs, &eventHandler, &eventDispatcher);
//    Subscription s0("binance-usds-futures", "btcusdt", "MARKET_DEPTH", "MARKET_DEPTH_MAX=20", "depth");
//    Subscription s1("binance-usds-futures", "ethusdt", "MARKET_DEPTH", "MARKET_DEPTH_MAX=20", "depth");
//    Subscription s2("binance-usds-futures", "btcusdt", "AGG_TRADE", "", "agg_trade");
//    Subscription s3("binance-usds-futures", "ethusdt", "AGG_TRADE", "", "agg_trade");
    Subscription s4("binance-usds-futures", "btcusdt", "MARK_PRICE", "", "mark_price");
    Subscription s5("binance-usds-futures", "", "MARK_PRICE", "", "mark_price");

//    std::vector<Subscription> subscription_list = {s0, s1, s2, s3, s4, s5};
    std::vector<Subscription> subscription_list = {s5};
    session.subscribe(subscription_list);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    session.stop();
    eventDispatcher.stop();
  } else if (mode == "handle_events_in_batching_mode") {
    SessionOptions sessionOptions;
    SessionConfigs sessionConfigs;
    Session session(sessionOptions, sessionConfigs);
    Subscription subscription("binance-usds-futures", "ethusdt", "MARKET_DEPTH", "", "binance-us__ethusd");
    session.subscribe(subscription);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::vector<Event> eventList = session.getEventQueue().purge();
    for (const auto& event : eventList) {
      std::cout << toString(event) + "\n" << std::endl;
    }
    session.stop();
  }
  std::cout << "Bye" << std::endl;
  return EXIT_SUCCESS;
}
