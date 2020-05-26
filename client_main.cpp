
//client side
#include "client_client.h"

int main(int argc, char const *argv[]) {
    Client client(argv[1], argv[2]);

    client();

    return 0;
}
