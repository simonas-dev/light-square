//
// Created by Simonas Sankauskas on 2019-04-26.
//

#include "BoxClient.h"

BoxResult<FcState> BoxClient::getState() {
    ofxHTTP::GetRequest request(stateUrl);

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

BoxResult<bool> get(ofxHTTP::Client client, string url) {
    BoxResult<FcState> result = BoxResult<FcState>();
    try
    {
        auto response = client.execute(url);

        // Check the response.
        if (response->getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
        {
            // A successful response.
            ofLogNotice("ofApp::setup") << "Response success, expecting " << response->estimatedContentLength() << " bytes.";

            // Buffer the response, or otherwise consume the stream.
            ofJson responseJson = response->json();

            ofLogNotice("ofApp::setup") << "Content Begin";

            std::cout << responseJson.dump(4) << std::endl;
            ofLogNotice("ofApp::setup") << "Content End";

        }
        else
        {
            ofLogError("ofApp::setup") << response->getStatus() << " " << response->getReason();
        }
    }
    catch (const Poco::Exception& exc)
    {
        ofLogError("ofApp::setup") << exc.displayText();
    }
    catch (const std::exception& exc)
    {
        ofLogError("ofApp::setup") << exc.what();
    }
}
