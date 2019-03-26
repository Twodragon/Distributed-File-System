//
// Created by Сергей Ефимочкин on 2019-02-19.
//

#include "Clients_Group.h"
#include <sstream>

void Clients_Group::parse(server_participant_ptr client, std::string message){
    if (message.find(std::string("started")) == 0) {
        (*client).write_possible_sequence("overall size");
    }

    if (message.find(std::string("command")) == 0) {
        parse_command_and_do_something(message);
    }
}

    void Clients_Group::parse_command_and_do_something(std::string message){
        std::istringstream iss(message);
        std::string command;
        std::string first_arg;
        std::string second_arg;
        std::string trash;
        int id = -1;

        if (iss)
            iss >> trash;
        if (iss)
            iss >> command;
        if (iss)
            iss >> trash;
        if (iss)
            iss >> id;
        if (iss)
            iss >> trash;
        if (iss)
            iss >> first_arg;
        if (iss)
            iss >> trash;
        std::getline(iss, second_arg);
        if (second_arg.length() > 0)
            second_arg = second_arg.substr(1);
        if (first_arg.find("second_arg:") == 0)
            first_arg = "";


        //printf("got command: %s\n", command.c_str());

        if (message.find(std::string("send")) == 0) {
            printf("sending to slaves_group!\n");
            other_group_->send_command(message);
        }

        else {

            std::string answer = "command: print id: " + std::to_string(id) + " first_arg: _ second_arg: " + fs.do_command(id, command, first_arg, second_arg);
            printf("sending answer: %s\n", answer.c_str());
            participants_[id]->write_possible_sequence(answer);
        }

    }

void Clients_Group::send_command(std::string message) {
    int client_id = -1;

    std::istringstream iss(message);
    std::string command;
    //std::string id_str;
    std::string first_arg;
    std::string second_arg;
    std::string trash;

    if (iss)
        iss >> trash;
    if (iss)
        iss >> command;
    if (iss)
        iss >> trash;
    if (iss)
        iss >> client_id;
    if (iss)
        iss >> trash;
    if (iss)
        iss >> first_arg;
    if (iss)
        iss >> trash;
    std::getline(iss, second_arg);
    if (second_arg.length() > 0)
        second_arg = second_arg.substr(1);

    if (command.find(std::string("send")) == 0) {
        participants_[client_id]->write_possible_sequence(message);
    }

    else if (command.find(std::string("read_whole")) == 0){
        participants_[client_id]->write_possible_sequence(message);
    }

    else if (command.find(std::string("freed_whole")) == 0){
    }
    //(*winner).write_possible_sequence(message);
}

void Clients_Group::do_something_on_leave(int server_id) {
    fs.client_leave(server_id);
}