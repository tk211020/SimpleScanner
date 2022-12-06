//U10516010Â²µ®¸`  scanner §@·~
#include <stdio.h>
#include <stdlib.h>

FILE *input;
FILE *output;

#define amount 9999

int main() {
	double test1 = 2.5;
	double test2 = 2.;
	double test3 = 2.5e+5;
	char next_char;
	char *iden[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "_"};	// word and _
	char *rewd[] = {"if", "else", "while", "for", "do", "switch", "case", "default", "continue", "int", "float", "double", "char", "break", "ststic", "extern", "auto", "register", "sizeof", "union", "struct", "enum", "return", "goto", "const"};		// reserve word
	char *digit[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};		//digit
	char str[255]; // store to determine reserve word or identify 
	int count_line = 1;		//count the line number
	
	input = fopen("scanner.c","r");		// open file and read
	output = fopen("output.txt", "w");		// write file named output
	
	// error when  open file
	if(input == NULL){
		printf("OPEN FILE ERROR");
	}
	
	fscanf(input, "%c", &next_char);		// read first char
	
	/* while file is not EOF, 
		deal with every char and output */ 
	while(!feof(input)) {
		
		int u;
		for(u = 0; u < sizeof(str); u++) {	// refresh the str array
			str[u] = '\0';
		}
		int bit = 0;	// str[bit]
		int var = 0;	// judge this char is word or _ , if yes, var = 1
		int i;
		
	
		// if change to next line and count_line + 1
		if(next_char == '\n') {
		 	count_line++;
		}
		
		// judge PREP, when encounter #, then print this line and count_line + 1
		else if(next_char == '#') {
			fprintf(output, "%d\tPREP \t\t", count_line);
			while(next_char != '\n') {
				fprintf(output, "%c", next_char);
				fscanf(input, "%c", &next_char);
			}
			fprintf(output,"\n");
			count_line++;
		}
		
		else if(next_char == '/') {
			fscanf(input, "%c", &next_char);
			
			// judge SC, when encounter //, then print this line and count_line + 1
			if(next_char == '/') {
				fprintf(output, "%d\tSC \t\t", count_line);
				fprintf(output, "%c", next_char);
				while(next_char != '\n') {
					fprintf(output, "%c", next_char);
					fscanf(input, "%c", &next_char);
				}
				if(next_char == '\n') {
		 			count_line++;
				} 
				fprintf(output,"\n");
			}
			
			// judge OPER, when encounter /=, then print operator /=
			else if(next_char == '=') {
				fprintf(output, "%d\tOPER \t\t", count_line);
				fprintf(output, "/");
				fprintf(output, "%c", next_char);
				fprintf(output,"\n");
			}
			
			// judge MC, when encounter /* until encounter */, then print line number and MC 
			else if(next_char == '*') {
				fprintf(output, "%d", count_line);
				while(1) {		
					if(next_char == '\n') {
				 		count_line++;
					}
					if(next_char == '*') {
						fscanf(input, "%c", &next_char);
						if(next_char == '/') {
							fscanf(input, "%c", &next_char);
							break;	
						}
					}

					fscanf(input, "%c", &next_char);
				}
				fprintf(output, "-%d\tMC", count_line);
				if(next_char == '\n') {
				 		count_line++;
				}
				fprintf(output,"\n");
			}
			
			// judge OPER, when encounter /, then print operator /
			else {
				fprintf(output, "%d\tOPER \t\t", count_line);
				fprintf(output, "/");
				fprintf(output,"\n");
			}
		}
		
		// judge SPEC, when encounter ( or ) or { or } or ;, then print this operator (){};
		else if(next_char == '(' || next_char == ')' || next_char == '{' || next_char == '}' || next_char == ';') {
			fprintf(output, "%d\tSPEC \t\t", count_line);
			fprintf(output, "%c", next_char);
			fprintf(output,"\n");
		}
		
		// judge STR, when encounter " until ", if encounter escape character, print "\""
		else if(next_char == '"') {
			fprintf(output, "%d\tSTR \t\t", count_line);
			fprintf(output, "%c", next_char);
			fscanf(input, "%c", &next_char);
			while(next_char != '"') {
				if(next_char == '\\') {
					fprintf(output, "%c", next_char);
					fscanf(input, "%c", &next_char);
				}
				fprintf(output, "%c", next_char);
				fscanf(input, "%c", &next_char);
				if(next_char == '\n') {
		 			count_line++;
				}
			}
			fprintf(output, "%c", next_char);
			fprintf(output,"\n");
		}
		
		// judge CHAR, when encounter ' until ', if encounter escape character, print '\''
		else if(next_char == '\'') {
			fprintf(output, "%d\tCHAR \t\t", count_line);
			fprintf(output, "%c", next_char);
			fscanf(input, "%c", &next_char);
			 
			while(next_char != '\'') {
				if(next_char == '\\') {
					fprintf(output, "%c", next_char);
					fscanf(input, "%c", &next_char);
				}
				fprintf(output, "%c", next_char);
				fscanf(input, "%c", &next_char);
			}
			fprintf(output, "%c", next_char);
			fprintf(output,"\n");
		}
		
		// if encounter \\ , print \\ in the file
		else if(next_char == '\\') {
			fscanf(input, "%c", &next_char);
			fprintf(output, "%c", next_char);
			if(next_char == '\\') {
				fprintf(output, "%c", next_char);
			}
		}
		
		// judge OPER, when encounter +, then print operator +
		else if(next_char == '+') {
			fprintf(output, "%d\tOPER \t\t", count_line);
			fprintf(output, "%c", next_char);
			fscanf(input, "%c", &next_char);
			
			// judge OPER, when encounter ++, then print operator ++
			if(next_char == '+') {
				fprintf(output, "%c", next_char);
			}
			
			// judge OPER, when encounter +=, then print operator +=
			else if(next_char == '=') {
				fprintf(output, "%c", next_char);
			}
			fprintf(output,"\n");
		}
		
		// judge OPER, when encounter -, then print operator -
		else if(next_char == '-') {
			fprintf(output, "%\tOPER \t\t", count_line);
			fprintf(output, "%c", next_char);
			fscanf(input, "%c", &next_char);
			
			// judge OPER, when encounter --, then print operator --
			if(next_char == '-') {
				fprintf(output, "%c", next_char);
			}
			
			// judge OPER, when encounter -=, then print operator -=
			else if(next_char == '=') {
				fprintf(output, "%c", next_char);
			}
			
			// judge OPER, when encounter ->, then print operator ->
			else if(next_char == '>') {
				fprintf(output, "%c", next_char);
			}
			fprintf(output,"\n");
		}
		
		// judge OPER, when encounter *, then print operator *
		else if(next_char == '*') {
			fprintf(output, "%d\tOPER \t\t", count_line);
			fprintf(output, "%c", next_char);
			fscanf(input, "%c", &next_char);

			// judge OPER, when encounter *=, then print operator *=
			if(next_char == '=') {
				fprintf(output, "%c", next_char);
			}
			fprintf(output,"\n");
		}
		
		// judge int and float
		else if(next_char == '0' || next_char == '1' || next_char == '2' || next_char == '3' || next_char == '4' || next_char == '5' || next_char == '6' || next_char == '7' || next_char == '8' || next_char == '9' || next_char == '.') {
			char string[amount];
			int i = 0;
			int dot = 0;		// to undicate this string have dot or not
			int english = 0;	// to judge this string have english word or not
			
			int now = 0;		// if this char is english word, store this char into str array
			
			// judge this string have dot or not, if yes, this string is float
			if(next_char == '.') {
				string[0] = next_char;
				fscanf(input, "%c", &next_char);
				dot = 1;
				// this dot is an operator
				if(next_char != '0' && next_char != '1' && next_char != '2' && next_char != '3' && next_char != '4' && next_char != '5' && next_char != '6' && next_char != '7' && next_char != '8' && next_char != '9') {
					fprintf(output, "%d\tOPER \t\t", count_line);
					fprintf(output, "%c", next_char);
					fprintf(output,"\n");
				}
			}
			
			// this dor is a float
			while(next_char == '0' || next_char == '1' || next_char == '2' || next_char == '3' || next_char == '4' || next_char == '5' || next_char == '6' || next_char == '7' || next_char == '8' || next_char == '9' || next_char == 'E' || next_char == 'e' || next_char == '+' || next_char == '-' || next_char == '.') {
				string[i] = next_char;
				fscanf(input, "%c", &next_char);
				if(next_char == '.') {
					dot = 1;
				}
				i++;
			}
			
			// judge behind the digit have english word or not
			while(next_char != '\n') {
				int j;
				now = 0;
				for(j = 0; j < 53; j++) {
					if(next_char == *iden[j]) {
						now = 1;
					}
				}
				// read char until this char is not english word
				if(now == 1) {
					string[i] = next_char;
					fscanf(input, "%c", &next_char);
					english = 1;
					i++;
				}
				else if(now == 0) {
					break;
				}
			}
			
			// digit + english word is an error token
			if(english == 1) {
				fprintf(output, "%d\terror token \t", count_line);
				int j;
				for(j = 0; j < i; j++) {
					fprintf(output, "%c", string[j]);
				}
				
				fprintf(output,"\n");
			}
			
			// print float number
			else if(next_char != '0' && next_char != '1' && next_char != '2' && next_char != '3' && next_char != '4' && next_char != '5' && next_char != '6' && next_char != '7' && next_char != '8' && next_char != '9' && next_char != 'E' && next_char != 'e' && next_char != '+' && next_char != '-' && next_char != '.' && dot == 1 && english == 0) {
				fprintf(output, "%d\tFLOT \t\t", count_line);
				int j;
				for(j = 0; j < i; j++) {
					fprintf(output, "%c", string[j]);
				}
				fprintf(output,"\n");
			}
			
			// print int number
			else if(next_char != '0' && next_char != '1' && next_char != '2' && next_char != '3' && next_char != '4' && next_char != '5' && next_char != '6' && next_char != '7' && next_char != '8' && next_char != '9' && dot == 0 && english == 0) {
				fprintf(output, "%d\tINTE \t\t", count_line);
				int j;
				for(j = 0; j < i; j++) {
					fprintf(output, "%c", string[j]);
				}
				fprintf(output,"\n");
			}	
			
			if(next_char == '(' || next_char == ')' || next_char == '{' || next_char == '}' || next_char == ';') {
				fprintf(output, "%d\tSPEC \t\t", count_line);
				fprintf(output, "%c", next_char);
				fprintf(output,"\n");
			}
			
			else if(next_char == '[' || next_char == ']' || next_char == '^' || next_char == ':') {
				fprintf(output, "%d\t OPER \t\t", count_line);
				fprintf(output, "%c", next_char);
				fprintf(output,"\n");
			}
		}
		
		// judge OPER, when encounter ,, then print operator ,
		else if(next_char == ',') {
			fprintf(output, "%d\tOPER \t\t", count_line);
			fprintf(output, "%c", next_char);
			fprintf(output,"\n");
		}
		
		// judge OPER, when encounter =, then print operator =
		else if(next_char == '=') {
			fprintf(output, "%d\tOPER \t\t", count_line);
			fprintf(output, "%c", next_char);
			fscanf(input, "%c", &next_char);
			
			// judge OPER, when encounter ==, then print operator ==
			if(next_char == '=') {
				fprintf(output, "%c", next_char);
			}
			fprintf(output,"\n");
		}
		
		// judge OPER, when encounter %, then print operator %
		else if(next_char == '%') {
			fprintf(output, "%d\tOPER \t\t", count_line);
			fprintf(output, "%c", next_char);
			fscanf(input, "%c", &next_char);
			
			// judge OPER, when encounter %=, then print operator %=
			if(next_char == '=') {
				fprintf(output, "%c", next_char);
			}
			fprintf(output,"\n");
		}
		
		// judge OPER, when encounter >, then print operator >
		else if(next_char == '>') {
			fprintf(output, "%d\tOPER \t\t", count_line);
			fprintf(output, "%c", next_char);
			fscanf(input, "%c", &next_char);
			
			// judge OPER, when encounter >>, then print operator >>
			if(next_char == '>') {
				fprintf(output, "%c", next_char);
			}
			
			// judge OPER, when encounter >=, then print operator >=
			else if(next_char == '=') {
				fprintf(output, "%c", next_char);
			}
			
			fprintf(output,"\n");
		}
		
		// judge OPER, when encounter <, then print operator <
		else if(next_char == '<') {
			fprintf(output, "%d\tOPER \t\t", count_line);
			fprintf(output, "%c", next_char);
			fscanf(input, "%c", &next_char);
			
			// judge OPER, when encounter <<, then print operator <<
			if(next_char == '<') {
				fprintf(output, "%c", next_char);
			}
			
			// judge OPER, when encounter <=, then print operator <=
			else if(next_char == '=') {
				fprintf(output, "%c", next_char);
			}
			
			fprintf(output,"\n");
		}
		
		// judge OPER, when encounter !, then print operator !
		else if(next_char == '!') {
			fprintf(output, "%d\tOPER \t\t", count_line);
			fprintf(output, "%c", next_char);
			fscanf(input, "%c", &next_char);
			
			// judge OPER, when encounter !=, then print operator !=
			if(next_char == '=') {
				fprintf(output, "%c", next_char);
			}
			fprintf(output,"\n");
		}
		
		// judge OPER, when encounter &, then print operator &
		else if(next_char == '&') {
			fprintf(output, "%d\tOPER \t\t", count_line);
			fprintf(output, "%c", next_char);
			fscanf(input, "%c", &next_char);
			
			// judge OPER, when encounter &&, then print operator &&
			if(next_char == '&') {
				fprintf(output, "%c", next_char);
			}
			fprintf(output,"\n");
		}
		
		// judge OPER, when encounter |, then print operator |
		else if(next_char == '|') {
			fprintf(output, "%d\tOPER \t\t", count_line);
			fprintf(output, "%c", next_char);
			fscanf(input, "%c", &next_char);
			
			// judge OPER, when encounter ||, then print operator ||
			if(next_char == '|') {
				fprintf(output, "%c", next_char);
			}
			fprintf(output,"\n");
		}
		
		// judge OPER, when encounter [ or ] or ^ or :, then print operator []^:
		else if(next_char == '[' || next_char == ']' || next_char == '^' || next_char == ':') {
			fprintf(output, "%d\tOPER \t\t", count_line);
			fprintf(output, "%c", next_char);
			fprintf(output,"\n");
		}
		
		// judge this char is word or _ , if yes, var = 1 
		for(i = 0; i < 53; i++) {
			if(next_char == *iden[i]){
				var = 1;
			}
		}
		
		/* judge the string first char is english word or _
			if yes, flag = 1
			and store this char into str array*/
		if(var == 1) {
			int flag = 0;
			while(1) {
				int k;
				for(k = 0; k < 53; k++) {
					if(next_char == *iden[k]) {
						flag = 1;
					}
				}
				for(k = 0; k < 10; k++) {
					if(next_char == *digit[k]) {
						flag = 1;
					}
				}
				
				if(flag == 1) {
					str[bit] = next_char;
					bit++;
					fscanf(input, "%c", &next_char);
					flag = 0;
				}
				else if(flag == 0) {
					break;
				}
			}
			str[bit] = '\0';	// add \0 behind str array
			int l;
			int same = 0;		// compare str array and reserved word is same or not
			// compare 25 reserved word, if same, same = 1
			for(l = 0; l < 25; l++) {
				if(!strcmp(str, rewd[l])) {
					same = 1;
				}
			}
			//is reserved word, print REWD and the content of str array
			if(same == 1) {
				fprintf(output, "%d\tREWD \t\t", count_line);
				int r;
				for(r = 0; r < sizeof(str); r++) {
					fprintf(output, "%c", str[r]);
				}
				fprintf(output,"\n");
			}
			// if not reserved word, this variable is identify, print IDEN and the content of str array
			else{
				fprintf(output, "%d\tIDEN \t\t", count_line);
				int r;
				for(r = 0; r < sizeof(str); r++) {
					fprintf(output, "%c", str[r]);
				}
				fprintf(output,"\n");
			}
			if(flag==0){
				continue;
			}
	    
		}

			fscanf(input, "%c", &next_char);		// find next char

	}
	
	fclose(input);		// close the input file
	fclose(output);		// close the output file
}

