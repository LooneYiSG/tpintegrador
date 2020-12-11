#include <Windows.h>

char* unconstchar(const char* s) {
    int i;
    char* res = NULL;
    res = (char*) malloc(strlen(s)+1);
        for (i = 0; s[i] != '\0'; i++) {
            res[i] = s[i];
        }
        res[i] = '\0';
        return res;
}

void printfn(const char *palabra){
	char *H = unconstchar(palabra);
	for(int i=0;i<=strlen(H);i++){
		if(H[i]!='\0'){
			printf("%c",H[i]);
			Sleep(15);
		}
	}
}
