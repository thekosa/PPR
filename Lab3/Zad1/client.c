/* ********************************************** */
/* Na podstawie: http://xmlrpc-c.sourceforge.net  */
/* ********************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <xmlrpc-c/base.h>
#include <xmlrpc-c/client.h>

#define NAME "Xmlrpc-c Test Client"
#define VERSION "1.0"
//======================================================================
static void 
dieIfFaultOccurred (xmlrpc_env * const envP) {
    if (envP->fault_occurred) {
        fprintf( stderr, "ERROR: %s (%d)\n", envP->fault_string, envP->fault_code );
        exit(1);
    }
}
//======================================================================
int main(int const argc, char* argv[]){

	/* zmienne predefiniowane *****************************************/
    const char * const serverUrl = "http://localhost:12345/RPC2";
    const char * const methodName = "sample.add";
    int pierwsza = 0;
    int druga = 0;
	
	/* zmienne niezainicjowane ****************************************/
    xmlrpc_env env;
    xmlrpc_value * resultP;
    xmlrpc_int32 sum;
    
    /* inicjujemy srodowisko ******************************************/
    xmlrpc_env_init(&env);

    /* inicjujemy xml-rpc po stronie klienta **************************/
    xmlrpc_client_init2(&env, XMLRPC_CLIENT_NO_FLAGS, NAME, VERSION, NULL, 0);
    dieIfFaultOccurred(&env);	// sprawdzamy, czy wystapil blad 

    /* wywolujemy zdalna procedure ************************************/
    /* ("ii") oznacza format danych, tutaj: 2 x int *******************/
    pierwsza = atoi(argv[1]);
    druga = atoi(argv[2]);
    resultP = xmlrpc_client_call(&env, serverUrl, methodName, "(ii)", (xmlrpc_int32)pierwsza, (xmlrpc_int32)druga);
    dieIfFaultOccurred(&env);
    
    /* pobieramy wynik ************************************************/
    xmlrpc_read_int(&env, resultP, &sum);
    dieIfFaultOccurred(&env);
    
    /* wypisujemy wynik ***********************************************/
    printf("Wynik: %d\n", sum);
    
    /* dekrementujemy licznik referencji ******************************/
    xmlrpc_DECREF(resultP);

    /* czyscimy srodowisko ********************************************/
    xmlrpc_env_clean(&env);
    
    /* konczymy prace klienta *****************************************/
    xmlrpc_client_cleanup();

    return 0;
}
//======================================================================
