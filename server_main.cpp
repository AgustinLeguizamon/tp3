//
// Created by agustin on 23/5/20.
//

#include "server_file_reader.h"
#include "server_menssenger.h"
#include "server_server.h"


int main(int argc, char const *argv[]) {
    try{
        FileReader file_reader(argv[2]);
        Server server(file_reader, argv[1]);
        server();
    } catch(std::exception &e){
        printf("%s", e.what());
        return 1;
    } catch(...){
        printf("Unknow error!");
        return 1;
    }
    return 0;
}
