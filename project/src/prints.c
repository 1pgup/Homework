#include "prints.h"

void input_prompt() {
    printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n\n");
}
void input_prompt_client_inf() {
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
                "1 Number account: ",
                "2 Client name: ",
                "3 Surname: ",
                "4 Addres client: ",
                "5 Client Telnum: ",
                "6 Client indebtedness: ",
                "7 Client credit limit: ",
                "8 Client cash payments:");
}
void input_prompt_transfer_inf() {
    printf("%s\n%s\n\n",
                "1 Number account:",
                "2 Client cash payments: ");
}
