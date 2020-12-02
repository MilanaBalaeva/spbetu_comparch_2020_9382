#include <stdio.h>
#include <string.h>
#define NMAX 80

void transform(char* str_in, char* str_out){
	__asm__ __volatile__(".intel_syntax noprefix\n\t"
		"transf:\n\t"
			"cld\n\t"
			"mov al, [esi]\n\t"
			"cmp al, '0'\n\t"
			"jl loop_end\n\t"
			"cmp al, '9'\n\t"
			"jg loop_end\n\t"

			"sub al, '0'\n\t"
			"xor cx, cx\n\t" //stack index
			"to_bin:\n\t"
				"mov ah, al\n\t"
				"and ah, 1\n\t"
				"add ah, '0'\n\t"
				"push ax\n\t"
				"inc cx\n\t"
				"shr al, 1\n\t"
				"cmp al, 0\n\t"
				"jne to_bin\n\t"

			"write_bits:"
				"pop ax\n\t"
				"xchg ah, al\n\t"
				"stosb\n\t"
				"dec cx\n\t"
				"cmp cx, 0\n\t"
				"jne write_bits\n\t"
			"inc esi\n\t"
			"jmp transf\n\t"

			"loop_end:\n\t"
				"movsb\n\t"
				"cmp al, 0\n\t"
				"jne transf\n\t"
		:
		:"S" (str_in), "D" (str_out)
		:"%ax", "%cx", "%esp"	
	);
}

int main(){
	printf("Type of transformation: decimal digits into binary.\n");
	printf("Made by Balaeva M.\n");
	char str_in[NMAX];
	fgets(str_in, NMAX, stdin);
	*strstr(str_in, "\n") = 0;
	char str_out[NMAX * 4];
	transform(str_in, str_out);
	printf("%s\n", str_out);
	return 0;
}


