#include <at898252.h>

sfr IN = 0x80;

#define EMPTY 0xFF
#define CLEAR 0x14
#define EQUALS 0x15
#define BUFFER_SIZE 127

void read();
int calculate();
void show(int number);
unsigned char getFromIn();

//const int(*)(int a, int b) operations[4];
int buffer [BUFFER_SIZE];
int iterator = 0; 

main(){
	while(1){
		read();
		show(calculate());
	}
}

void read(){
	unsigned char input = 0;
	int i;
	for(i = 0; i < 4; i++){
	    int temp = getFromIn();
		if(temp < 0xF) input = (input << 4) | temp;
		else if(temp < CLEAR){
			buffer[iterator++] = input;
			//if(iterator > 0 && buffer[iterator - 1] < CLEAR)
			// TODO evtl prüfen: Zwei Operatoren hintereinander??	
			buffer[iterator] = temp;
			break;
		} 
		else  return;
	}
	read();
}

unsigned char getFromIn() {
	unsigned char temp;
 	while(IN == EMPTY);
	temp = IN;
	while(IN == temp);
	return temp;
}