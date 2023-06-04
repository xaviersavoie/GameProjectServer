#ifndef PARSER_HPP
#define PARSER_HPP

#include <nlohmann/json.hpp>
#include <sstream>
#include <memory>
#include <vector>
#include <CPacket.hpp>
#include <string>

using json = nlohmann::json;

class Parser {

public:
Parser();

std::stringstream& push_front( std::stringstream& sstm, const std::string& str );

typedef std::vector<std::shared_ptr<CPacket>> packets_ptr_vec;

std::stringstream ss_;
std::string prepend_string_;

int last_parse_pos_;

void put_into_internal_string_stream(std::string str);

std::vector<json> extract_json_blobs_from_internal_string_stream(int &last_parse_pos);

packets_ptr_vec get_packets_from_json_blobs(std::vector<json> json_blobs); 

std::shared_ptr<CPacket> infer_and_get_packet_ptr(json packet);

};

#endif
