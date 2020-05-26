
#include "client_client.h"

int main(int argc, char const *argv[]) {
    try{
        Client client(argv[1], argv[2]);
        client();
    } catch(std::exception &e){
        printf("%s", e.what());
        return 1;
    } catch(...){
        printf("Unknow error!");
        return 1;
    }
    return 0;
}
