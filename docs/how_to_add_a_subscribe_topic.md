### add a topic forceOrder to binance
1. MarketDataMessage, DataType ADD FORCE_ORDER, dataTypeToString add FORCE_ORDER
2. MarketDataMessage， DataFieldType add force order field, dataFieldTypeToString add field
3. add these codes to macro.h
    ```CPP
    #define CCAPI_WEBSOCKET_BINANCE_BASE_CHANNEL_FORCE_ORDER "force_order"
    #ifndef CCAPI_FORCE_ORDER
    #define CCAPI_MARK_PRICE "FORCE_ORDER"
    #endif
    ```
4. createSendStringList function add these codes:
    ```cpp
    else if (channelId.rfind(CCAPI_WEBSOCKET_BINANCE_BASE_CHANNEL_FORCE_ORDER, 0) == 0){
    
              if (symbolId.empty()){
                exchangeSubscriptionId = "!forceOrder@arr";
              }else{
                exchangeSubscriptionId = symbolId+"@forceOrder";
              }
              std::cout << "force_order exchangeSubscriptionId " << exchangeSubscriptionId << std::endl;
            }
    ```
5. add codes to processTextMessage in ccapi_market_data_service_binance_base.h

   ```cpp
   else if (channelId == CCAPI_WEBSOCKET_BINANCE_BASE_CHANNEL_FORCE_ORDER){
           // 订阅强平订单数据
           std::cout << "begin to deal force_order data " << std::endl;
           // 检查 "o" 是否存在并且是一个对象
           if (data.HasMember("o") && data["o"].IsObject()) {
             const rapidjson::Value& o_dict = data["o"];
             // 遍历 "o" 对象的键值对
             auto time = UtilTime::makeTimePointFromMilliseconds(std::stoll(o_dict["T"].GetString()));
             MarketDataMessage marketDataMessage;
             marketDataMessage.type = MarketDataMessage::Type::MARKET_DATA_EVENTS_FORCE_ORDER;
             marketDataMessage.exchangeSubscriptionId = exchangeSubscriptionId;
             marketDataMessage.tp = time;
             marketDataMessage.recapType = MarketDataMessage::RecapType::NONE;
             MarketDataMessage::TypeForDataPoint dataPoint;
             dataPoint.insert({MarketDataMessage::DataFieldType::ORDER_SIDE,
                               o_dict["S"].GetString()});
             dataPoint.insert({MarketDataMessage::DataFieldType::ORDER_TYPE,
                               o_dict["o"].GetString()});
             dataPoint.insert({MarketDataMessage::DataFieldType::ORDER_FORCE,
                               o_dict["f"].GetString()});
             dataPoint.insert({MarketDataMessage::DataFieldType::ORDER_QTY,
                               UtilString::normalizeDecimalString(std::string(o_dict["q"].GetString()))});
             dataPoint.insert({MarketDataMessage::DataFieldType::ORDER_PRICE,
                               UtilString::normalizeDecimalString(std::string(o_dict["p"].GetString()))});
             dataPoint.insert({MarketDataMessage::DataFieldType::ORDER_AVG_PRICE,
                               UtilString::normalizeDecimalString(std::string(o_dict["ap"].GetString()))});
             dataPoint.insert({MarketDataMessage::DataFieldType::ORDER_STATUS,
                               o_dict["p"].GetString()});
             dataPoint.insert({MarketDataMessage::DataFieldType::ORDER_LAST_TRADE_QTY,
                               UtilString::normalizeDecimalString(std::string(o_dict["l"].GetString()))});
             dataPoint.insert({MarketDataMessage::DataFieldType::ORDER_CUMSUM_TRADE_QTY,
                               UtilString::normalizeDecimalString(std::string(o_dict["z"].GetString()))});
   
             marketDataMessage.data[MarketDataMessage::DataType::FORCE_ORDER].emplace_back(std::move(dataPoint));
             marketDataMessageList.emplace_back(std::move(marketDataMessage));
           } else if (doc.HasMember("o") && doc["o"].IsArray()) {
             // 如果 "o" 是一个数组
             const rapidjson::Value& oArray = doc["o"];
             // 遍历数组中的每个对象
             for (rapidjson::SizeType i = 0; i < oArray.Size(); i++) {
               const rapidjson::Value& o_dict = oArray[i];
               auto time = UtilTime::makeTimePointFromMilliseconds(std::stoll(o_dict["T"].GetString()));
               MarketDataMessage marketDataMessage;
               marketDataMessage.type = MarketDataMessage::Type::MARKET_DATA_EVENTS_FORCE_ORDER;
               marketDataMessage.exchangeSubscriptionId = exchangeSubscriptionId;
               marketDataMessage.tp = time;
               marketDataMessage.recapType = MarketDataMessage::RecapType::NONE;
               MarketDataMessage::TypeForDataPoint dataPoint;
               dataPoint.insert({MarketDataMessage::DataFieldType::ORDER_SIDE,
                                 o_dict["S"].GetString()});
               dataPoint.insert({MarketDataMessage::DataFieldType::ORDER_TYPE,
                                 o_dict["o"].GetString()});
               dataPoint.insert({MarketDataMessage::DataFieldType::ORDER_FORCE,
                                 o_dict["f"].GetString()});
               dataPoint.insert({MarketDataMessage::DataFieldType::ORDER_QTY,
                                 UtilString::normalizeDecimalString(std::string(o_dict["q"].GetString()))});
               dataPoint.insert({MarketDataMessage::DataFieldType::ORDER_PRICE,
                                 UtilString::normalizeDecimalString(std::string(o_dict["p"].GetString()))});
               dataPoint.insert({MarketDataMessage::DataFieldType::ORDER_AVG_PRICE,
                                 UtilString::normalizeDecimalString(std::string(o_dict["ap"].GetString()))});
               dataPoint.insert({MarketDataMessage::DataFieldType::ORDER_STATUS,
                                 o_dict["p"].GetString()});
               dataPoint.insert({MarketDataMessage::DataFieldType::ORDER_LAST_TRADE_QTY,
                                 UtilString::normalizeDecimalString(std::string(o_dict["l"].GetString()))});
               dataPoint.insert({MarketDataMessage::DataFieldType::ORDER_CUMSUM_TRADE_QTY,
                                 UtilString::normalizeDecimalString(std::string(o_dict["z"].GetString()))});
               
               marketDataMessage.data[MarketDataMessage::DataType::FORCE_ORDER].emplace_back(std::move(dataPoint));
               marketDataMessageList.emplace_back(std::move(marketDataMessage));
             }
           } else {
             std::cerr << "\"o\" is not an object or array." << std::endl;
           }
             // std::cout << "获取到了数据, 处理完成" << std::endl;
         }
   
   ```
6. add a function to ccapi_market_data_service.h
   ```cpp
   void processExchangeProvidedForceOrder(const WsConnection& wsConnection, const std::string& channelId, const std::string& symbolId, Event& event,
                                           const TimePoint& tp, const TimePoint& timeReceived, MarketDataMessage::TypeForData& input, const std::string& field,
                                           const std::map<std::string, std::string>& optionMap, const std::vector<std::string>& correlationIdList,
                                           bool isSolicited) {
       std::vector<Message> messageList;
       std::vector<Element> elementList;
       if (field == CCAPI_FORCE_ORDER) {
         for (auto& x : input) {
           auto& type = x.first;
           auto& detail = x.second;
           // std::cout << "type = " << MarketDataMessage::dataTypeToString(type) << std::endl;
           // std::vector<std::map<DataFieldType, std::string> >
           // std::cout << "detail size = " << detail.size() << std::endl;
           if (type == MarketDataMessage::DataType::FORCE_ORDER) {
             for (auto& y : detail) {
               auto& order_side = y.at(MarketDataMessage::DataFieldType::ORDER_SIDE);
               auto& order_type = y.at(MarketDataMessage::DataFieldType::ORDER_TYPE);
               auto& order_force = y.at(MarketDataMessage::DataFieldType::ORDER_FORCE);
               auto& order_qty = y.at(MarketDataMessage::DataFieldType::ORDER_QTY);
               auto& order_price = y.at(MarketDataMessage::DataFieldType::ORDER_PRICE);
               auto& order_avg_price = y.at(MarketDataMessage::DataFieldType::ORDER_AVG_PRICE);
               auto& order_status = y.at(MarketDataMessage::DataFieldType::ORDER_STATUS);
               auto& order_last_trade_qty = y.at(MarketDataMessage::DataFieldType::ORDER_LAST_TRADE_QTY);
               auto& order_cumsum_trade_qty = y.at(MarketDataMessage::DataFieldType::ORDER_CUMSUM_TRADE_QTY);
               
               Element element;
               std::string k1("order_side");
               std::string k2("order_type");
               std::string k3("order_force");
               std::string k4("order_qty");
               std::string k5("order_price");
               std::string k6("order_avg_price");
               std::string k7("order_status");
               std::string k8("order_last_trade_qty");
               std::string k9("order_cumsum_trade_qty");
               element.emplace(k1, order_side);
               element.emplace(k2, order_type);
               element.emplace(k3, order_force);
               element.emplace(k4, order_qty);
               element.emplace(k5, order_price);
               element.emplace(k6, order_avg_price);
               element.emplace(k7, order_status);
               element.emplace(k8, order_last_trade_qty);
               element.emplace(k9, order_cumsum_trade_qty);
               elementList.emplace_back(std::move(element));
             }
           } else {
             CCAPI_LOGGER_WARN("extra type " + MarketDataMessage::dataTypeToString(type));
           }
         }
       }
       if (!elementList.empty()) {
         Message message;
         message.setTimeReceived(timeReceived);
         message.setType(Message::Type::MARKET_DATA_EVENTS_FORCE_ORDER);
         message.setRecapType(isSolicited ? Message::RecapType::SOLICITED : Message::RecapType::NONE);
         message.setTime(tp);
         message.setElementList(elementList);
         message.setCorrelationIdList(correlationIdList);
         message.setSymbolId(symbolId);
         messageList.emplace_back(std::move(message));
       }
       if (!messageList.empty()) {
         event.addMessages(messageList);
       }
     }
   ```
7. add some codes to processMarketDataMessageList in ccapi_market_data_service.h
   ```cpp
   if (marketDataMessage.data.find(MarketDataMessage::DataType::FORCE_ORDER) != marketDataMessage.data.end()){
             bool isSolicited = marketDataMessage.recapType == MarketDataMessage::RecapType::SOLICITED;
             this->processExchangeProvidedForceOrder(wsConnection, channelId, symbolId, event, marketDataMessage.tp, timeReceived, marketDataMessage.data, field,
                                                    optionMap, correlationIdList, isSolicited);
           }
   
   ```