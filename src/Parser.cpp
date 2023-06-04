#include <Parser.hpp>

#include <nlohmann/json.hpp>
#include <sstream>
#include <memory>
#include <vector>

#include <CPacket.hpp>
#include <ClientEntityPositionPacket.hpp>

#include <string>
#include <iostream>


using json = nlohmann::json;

Parser::Parser() : last_parse_pos_(0) {}

//std::stringstream ss_;

std::stringstream& Parser::push_front( std::stringstream& sstm, const std::string& str )
{
    sstm.str( str + sstm.str() ) ;
    sstm.seekg(0);
    return sstm ;
}

void Parser::put_into_internal_string_stream(std::string str) {
    std::cout << "FROM PUT INTO: " << str << std::endl;
    ss_ << str;
}

std::vector<json> Parser::extract_json_blobs_from_internal_string_stream(int &last_parse_pos) {

    std::cout << "string stream contents: " << ss_.str() << std::endl;

    std::vector<json> return_vec;


    while (ss_.peek() != EOF) {
        std::cout << "ss size: " << ss_.str().size() << "\n";
        json json_obj_buf;
        try {
            ss_ >> json_obj_buf;
            if (!json_obj_buf.is_object()) continue;
            return_vec.emplace_back(json_obj_buf);
            if (last_parse_pos != -1) {
                last_parse_pos = ss_.tellg();
            }

            std::cout << "Last parse pos: " << last_parse_pos << std::endl;

        } catch (json::parse_error &e) {
            int on_err_pos = ss_.tellg();
            ss_.clear();
            ss_.seekg(on_err_pos);
            std::cout << "Last successful parse pos from catch block: " << last_parse_pos << std::endl;
            if (ss_.tellg() == -1) {
                ss_.clear();
                ss_.seekg(last_parse_pos);
                std::cout << "pos after seekg" << ss_.tellg() << std::endl;
                std::string temp_prepend_string;
                while(ss_.peek() != EOF) {
                    std::cout << "PEEK! : " << ss_.peek() << std::endl;
                    temp_prepend_string.push_back(ss_.get());
                }
                prepend_string_ = temp_prepend_string;
            }

            std::cerr << e.what() << std::endl;
            //std::cerr << "[ERR INFO] Last parse pos ON ERROR (not affected to last_parse_pos) on stringstream was at: " << ss_.tellg() << std::endl;
            //std::cerr << "[ERR INFO] contents of stringstream after err: " << ss_.str() << std::endl;
            

        }

    }
        ss_.str(std::string());
        ss_.clear();
        ss_ << prepend_string_;

    return return_vec;
}

Parser::packets_ptr_vec Parser::get_packets_from_json_blobs(std::vector<json> json_blobs) {
    Parser::packets_ptr_vec return_vec;
    for (int i = 0; i < json_blobs.size(); i++) {
        std::shared_ptr<CPacket> temp_ptr = infer_and_get_packet_ptr(json_blobs[i]); //Probably null check around here
        return_vec.emplace_back(temp_ptr);
    }
    return return_vec;
}

std::shared_ptr<CPacket> Parser::infer_and_get_packet_ptr(json packet) {
    std::string packetType = packet["packetType"].get<std::string>();
    if (typeid(packetType) != typeid(std::string)) {
        std::cout << "Wrong \"packetType\" value type" << std::endl;
        return nullptr;
    }

    if (packetType == "ClientEntityPosition") { //TODO: CHECKS ON PACKET CONTENTS
        std::vector<double> posVec = packet["position"];
        if (posVec.size() != 3) return nullptr;
        long entityID = packet["entityID"];
        return std::make_shared<ClientEntityPositionPacket>(posVec, entityID);
    } else {
        return nullptr;
    }
}
