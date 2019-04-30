//
// Created by Simonas Sankauskas on 2019-04-26.
//

#include "BoxClient.h"

BoxResult<FcState> BoxClient::getState() {
    ofxHTTP::GetRequest request(stateUrl);

//    try
//    {
//        // Execute the request within the given context.
//        auto response = client.execute(context, request);
//
//        // Check the response.
//        if (response->getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
//        {
//            // A successful response.
//            ofLogNotice("ofApp::setup") << "Response success, expecting " << response->estimatedContentLength() << " bytes.";
//
//            // Buffer the response, or otherwise consume the stream.
//            ofBuffer buffer(response->stream());
//
//            ofLogNotice("ofApp::setup") << "Content Begin";
//
//            std::cout << buffer << std::endl;
//
//            ofLogNotice("ofApp::setup") << "Content End";
//        }
//        else
//        {
//            ofLogError("ofApp::setup") << response->getStatus() << " " << response->getReason();
//        }
//    }
//    catch (const Poco::Exception& exc)
//    {
//        ofLogError("ofApp::setup") << exc.displayText();
//    }
//    catch (const std::exception& exc)
//    {
//        ofLogError("ofApp::setup") << exc.what();
//    }

    return BoxResult<FcState>();
}

BoxResult<FcConfig> BoxClient::getConfig() {
    return BoxResult<FcConfig>();
}

BoxResult<bool> BoxClient::setConfig(FcConfig model) {
    return BoxResult<bool>();
}

BoxResult<bool> BoxClient::start() {
    return BoxResult<bool>();
}

BoxResult<bool> BoxClient::stop() {
    return BoxResult<bool>();
}

BoxResult<bool> BoxClient::restart() {
    return BoxResult<bool>();
}
