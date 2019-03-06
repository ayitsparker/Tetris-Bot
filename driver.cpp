#include "driver.hpp"
#include <unordered_map>
#include <map>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>

/* Helper to autset settings */
#define DEFINE_LOOKUP_MAP(Type) std::map<std::string, std::string Type::*> mapper
#define ADD_FIELD_MAPPING(Type, Field) mapper[#Field]=&Type::Field
#define SET_FIELD_FROM_MAP(Type, Field, var, value) var.*(mapper[Field])=value

/* Begin code */
user_settings readSettings(){
    std::ifstream settings_file (USER_CONFIG);
    DEFINE_LOOKUP_MAP(user_settings);
    ADD_FIELD_MAPPING(user_settings, interface);
    ADD_FIELD_MAPPING(user_settings, username);
    ADD_FIELD_MAPPING(user_settings, password);
    user_settings retVal;

    if(settings_file.is_open()){

        std::unordered_map<std::string, std::string> settings_map;
        std::string current_line = "";

        std::cout << "Reading settings..." << std::endl;

        while(getline(settings_file, current_line)){
            std::vector<std::string> key_value;
            boost::split(key_value, current_line, boost::is_any_of(":"));

            if(key_value.size() != 2){
                std::cerr << "Found invalid settings for line: " << current_line << std::endl;
                exit(-1);
            }

            settings_map[key_value[0]] = key_value[1];
            SET_FIELD_FROM_MAP(user_settings, key_value[0], retVal, key_value[1]);    
        }

        return retVal;
    }
    std::cerr << "Cannot find user config file: " << USER_CONFIG << std::endl;
    exit(-1);
}

int main() {
    std::vector<Packet> vt;

    user_settings settings = readSettings();

    Sniffer sniffer("enp0s5");
    while (vt.size() != 10) {
        vt.push_back(sniffer.next_packet());
    }

    for (auto& packet : vt) {
        if (packet.pdu()->find_pdu<IP>()) {
	    PDU::serialization_type buffer = packet.pdu()->serialize();

	    printf("Found packet <");
	    for(int i = 0; i < buffer.size(); i++)
		printf("%d, ", buffer[i]);
	    printf(">\n");
       }
    }
}
