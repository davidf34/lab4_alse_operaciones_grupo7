//incluir librerias.
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_FILE_SIZE 1500

//definicion de prototipos
void leer();
void armatriz();
void fyc();
void suma();
void resta();
void transpuesta();
void escribir();
void ayuda(); 
void version();

//codigo principal
int main(int argc, char* argv[]){
	char h[MAX_FILE_SIZE];
	strcpy(h,argv[1]);// guarda en h el argumento
	char buffer1[MAX_FILE_SIZE];
	char buffer2[MAX_FILE_SIZE];
	char dir[MAX_FILE_SIZE];
	char dir2[MAX_FILE_SIZE];
	char dir3[MAX_FILE_SIZE];
	char dir4[MAX_FILE_SIZE];
	int i=0,j=0;
	int filas1=1,columnas1=1,filas2=1,columnas2=1;
	strcpy(dir,argv[2]);// guarda en dir el argumento
	strcpy(dir2,argv[3]);// guarda en dir2 el argumento
	strcpy(dir3,argv[4]);// guarda en dir3 el argumento
	strcpy(dir4,argv[5]);// guarda en dir4 el argumento
	leer(dir,buffer1);
	leer(dir2,buffer2);
	int filesize1=strlen(buffer1);
	int filesize2=strlen(buffer2);
	fyc(buffer1,&filas1,&columnas1,&filesize1);//cuenta filas y columnas de la matriz1
	fyc(buffer2,&filas2,&columnas2,&filesize2);//cuenta filas y columnas de la matriz2
	float mat1[filas1][columnas1];// se crean las matrices a rellenar
	float mat2[filas2][columnas2];
	float matr[filas2][columnas2];
	float matrs[columnas1][filas1];
	float matrs2[columnas2][filas2];
	armatriz(buffer1,&filesize1,&columnas1,&filas1,mat1);// se rellena la matriz
	armatriz(buffer2,&filesize2,&columnas2,&filas2,mat2);
	for (i=0;i<filas2;i++){
			for (j=0;j<columnas2 ;j++){
				printf("   %1.2f   ", mat1[i][j]);
			}
		printf("\n");
	}
	for (i=0;i<filas2;i++){
			for (j=0;j<columnas2 ;j++){
				printf("   %1.2f   ", mat2[i][j]);
			}
		printf("\n");
	}
	if (strcmp(h,"--help")== 0)
	{
		ayuda();//imprime la ayuda
	} 
	
	else if (strcmp(h,"-v")== 0)
	{
		version();//imprime la información
	} 
	
	else if (strcmp(h,"-t")== 0)// relaiza la transpuesta de cada matriz e imprime cada una
	{
		transpuesta(&filas1,&columnas1,mat1,matrs);
		for (i=0;i<columnas1;i++){
			for (j=0;j<filas1 ;j++){
				printf("   %1.2f   ", matrs[i][j]);
			}
		printf("\n");
		}	
		printf("\n\n");
		printf("\n\n"); 
		transpuesta(&filas2,&columnas2,mat2,matrs2);
		for (i=0;i<columnas2;i++){
			for (j=0;j<filas2 ;j++){
				printf("   %1.2f   ", matrs2[i][j]);
			}
			printf("\n");
		}	
		printf("\n\n");
		printf("\n\n"); 
	} 
	
	else if (strcmp(h,"-a")== 0)//realiza la suma de las matrices e imprime el resultado
	{
		suma(&filas1,&columnas1,&filas2,&columnas2,mat1,mat2,matr);
		for (i=0;i<filas2;i++){
			for (j=0;j<columnas2 ;j++){
				printf("   %1.2f   ", matr[i][j]);
			}
		printf("\n");
		}	
		printf("\n\n");
		printf("\n\n");
	} 
	
	else if (strcmp(h,"-r")== 0)//realiza la resta de las matrices e imprime el resultado
	{
		resta(&filas1,&columnas1,&filas2,&columnas2,mat1,mat2,matr);
		for (i=0;i<filas2;i++){
			for (j=0;j<columnas2 ;j++){
				printf("   %1.2f   ", matr[i][j]);
			}
			printf("\n");
		}	
		printf("\n\n");
		printf("\n\n");
	} 
	
	else if (strcmp(h,"-w")== 0)//realiza la operacion solicitada guarda el resultado en un archivo
	{//                            el archivo se crea y guarda en la direccion dada
		if (strcmp(dir4,"-a")== 0){//suma
			suma(&filas1,&columnas1,&filas2,&columnas2,mat1,mat2,matr);
			escribir(dir3,&filas2,&columnas2,matr);
		}
		else if (strcmp(dir4,"-r")== 0){//resta
			resta(&filas1,&columnas1,&filas2,&columnas2,mat1,mat2,matr);
			escribir(dir3,&filas2,&columnas2,matr);
		}
		else if (strcmp(dir4,"-ta")== 0){//transpuesta matriz1
			transpuesta(&filas1,&columnas1,mat1,matrs);
			escribir(dir3,&columnas1,&filas1,matrs);
		}
		else if (strcmp(dir4,"-tb")== 0){//transpuesta matriz2
			transpuesta(&filas2,&columnas2,mat2,matrs2);
			escribir(dir3,&filas2,&columnas2,matr);
		}
		else{//valida el argumento
		printf("Ingrese un argumento válido( -t, -a, -r, -ta,-tb)\n");
		}	
	
		
		
	}
	else{ //valida el argumento
		printf("Ingrese un argumento válido(--help, -v, -t, -a, -r, -w)\n");
	}
	
	return 0;
}
void leer(char* dir, char* buffer1){// leer archivo y guardarlo en buffer
	FILE *file_descriptor1;
	char prueba[MAX_FILE_SIZE];
	size_t result = 0;
	long file_size = 0;
	file_descriptor1 = fopen (dir,"r");
	
	fseek (file_descriptor1, 0, SEEK_END); //busca hasta el final
	
	file_size = ftell(file_descriptor1); //retorna al tamaño
	
	rewind (file_descriptor1); //rebobina al valor inicial
	
	result = fread (buffer1, 1 , file_size, file_descriptor1);
	
	if (result != file_size)
	{
		fputs("Error de escritura de buffer", stderr);
	
	}

	fclose(file_descriptor1);
	buffer1[file_size] = '\0';
	
}
void ayuda()// se imprimen las instrucciones
  
  {
		printf("\nEl presente programa se deben enviar siempre 6 argumentos al ejecutar el programa. \n");
		printf("\nEl programa siempre se debe ejecutar de la siguiente manera:\n");
		printf("\n./string.bin ARG1 ARG2 ARG3 ARG4 ARG5\n");
		printf("\nEn el argumento 2 y 3 se deben dar las direcciones de los archivos con las matrices a operar \n ");
		printf("\nEn el argumento 2, 3 y 4 se deben dar las direcciones con nombre incluido exacto del archivo \n ");
		printf("\nEl presente programa tiene las siguientes funciones: \n");
		printf("\nEl argumento 1 -v muestra la versión, autores y fecha de desarrollo. \n");
		printf("\nEl argumento 1 -t muestra la transpuesta de las matrices ingresadas en el archivo de extensión .CSV llamado matriz_1.csv y matriz_2.csv \n ");
		printf("\nEl argumento 1 -a muestra la suma de las matrices ingresadas en el archivo de extensión .CSV llamado matriz_1.csv y matriz_2.csv\n ");
		printf("\nEl argumento 1 -r muestra la resta de las matrices ingresadas en el archivo de extensión .CSV llamado matriz_1.csv y matriz_2.csv\n ");
		printf("\nEl argumento 1 -w Indica que el resultado de la operación se debe guardar en un archivo con formato CSV.\n ");
		printf("\nRecuerde que si guarda un archivo en la misma direccion y también tiene el mismo nombre, este se sobre-escribirá.\n ");
		printf("\nEl argumento 5 -a guarda la suma de las matrices en un archivo con nombre y dirección dadas en el argumento 4 \n ");
		printf("\nEl argumento 5 -r guarda la resta de las matrices en un archivo con nombre y dirección dadas en el argumento 4 \n ");
		printf("\nEl argumento 5 -tb guarda la transpuesta de la segunda matriz en un archivo con nombre y dirección dadas en el argumento 4 \n ");
		printf("\nEl argumento 5 -ta guarda la transpuesta de la primera matriz en un archivo con nombre y dirección dadas en el argumento 4 \n ");
  }
void version()// se imprimen la información
	
	{
		printf("\n Versión 1.0 \n");
		printf("\n Autores: Andres Gómez, David Sandoval.\n");	
		printf("\n Fecha de desarrollo 30/09/2020 \n");	
    }
void escribir(char* dir,int* columnas,int* filas, float matrix[][*columnas]){	
	char buffer1[MAX_FILE_SIZE]={""};
	int i=0,j=0,k=0;
	char o[MAX_FILE_SIZE];
	int f=*filas;
	int c=*columnas;
	for (i=0;i<f;i++){
		for (j=0;j<c;j++){ // dependiendo de la condición se convierte el numero float en char y va concantenando con ; o \r\n
			gcvt(matrix[i][j],6,o);//convierte float en char
			if(i+1==f && j+1==c){
					strcat(o,"\0");//concatena el final de cadena
					
				}
			else if(j+1==c){//concatena el carriage return y el final de linea
					
					strcat(o,"\r\n");
				}
			else {// concatena ; al final de convertir el numero
				strcat(o,";");
			} 
			
			strcat(buffer1,o);// concatena el char que era el numero
		}
		
	}
	
	long file_size=strlen(buffer1);
	buffer1[file_size] = '\0';
	FILE *file_descriptor1;
	size_t result = 0;
	file_descriptor1 = fopen (dir,"w");
	result = fwrite(buffer1, 1 , file_size, file_descriptor1);//escribe buffer1 en el archivo
	fclose(file_descriptor1);
	
	
} 
void transpuesta (int* filas1,int* columnas1, float mat1[][*columnas1],float matrs[][*filas1]){// intercambia filas y columnas de la matriz que se recibe

	int i=0, j=0;
	int f=*columnas1;
	int c=*filas1;
	
	for (i=0;i<f ;i++){
		for (j=0;j<c ;j++){
			matrs[i][j]=mat1[j][i];// intercambia filas y columnas
		}
	}
	printf("\n\n");
	

}
void fyc(char* buffer1, int* filas, int* columnas, int* file_size){// contador de filas y columnas recorriendo el buffer
	int i=0;
	int f=*file_size;
	int c=*columnas;
	int fi=*filas;
	for (i=0;i<=f;i++){//contar columnas en la primera linea del archivo
		if (buffer1[i]=='\r'){
				break;
			}
		if (buffer1[i]==';'){
				c=c+1;
			}
	}
	for (i=0;i<=f;i++){//contar filas en todo el archivo 
		if (buffer1[i]=='\r'){
				fi=fi+1;
			}
	}
	*file_size=f;
	*columnas=c;
	*filas=fi;
}
void suma(int* filas1,int* columnas1,int* filas2, int* columnas2,float mat1[][*columnas1],float mat2[][*columnas2], float matr[][*columnas1]){
	// suma las matrices
	int i=0,j=0;
	int f=*filas1;
	int c=*columnas1;
	int fi=*filas2;
	int co=*columnas2;
	if(f==fi & c==co){
		for (i=0;i<=f ;i++){
			for (j=0;j<=c ;j++){
				matr[i][j]=mat1[i][j]+mat2[i][j];// suma las matrices
			}
		}
	}
	else{// error en la suma 
		printf("\n NO SE PUEDE SUMAR\n");
	
	}
}
void resta(int* filas1,int* columnas1,int* filas2, int* columnas2,float mat1[][*columnas1],float mat2[][*columnas2], float matr[][*columnas1]){
	// resta las matrices
	int i=0,j=0;
	int f=*filas1;
	int c=*columnas1;
	int fi=*filas2;
	int co=*columnas2;
	if(f==fi & c==co){
		for (i=0;i<=f ;i++){
			for (j=0;j<=c ;j++){
				matr[i][j]=mat1[i][j]-mat2[i][j];// resta las matrices
			}
		}
	}
	else{// error en la resta
		printf("\n NO SE PUEDE RESTAR\n");
	
	}
}
void armatriz(char* buffer1, int* file_size,int* columnas, int* filas, float matrix[][*columnas]){
	int i=0;
	char prueba[MAX_FILE_SIZE];
	int f=*file_size;
	int c=*columnas;
	int fi=*filas;
	int k=0,j=0,b=0;
	float o=0;
	float paso[f];
	for (i=0;i<=f;i++){// recorre hasta encontrar ; guarda lo que encontro en prueba, lo convierte a float y lo guarda en paso
		if (buffer1[i]==';' | buffer1[i]=='\r'|  buffer1[i]=='\0' ){
			o=atof(prueba);
			for (b=0;b<MAX_FILE_SIZE;b++){
				prueba[b]='\0';
			} 
			if (buffer1[i]=='\n'){
				i++;
			}
			paso[k]=o;
			j=0;
			k++;
			i++;
		}
	prueba[j]=buffer1[i];
	j++;
		
	}//hasta aca guarda todo en paso
	k=0;
	for (i=0;i<fi;i++){// guardo en una matriz lo que hay en paso 
		for (j=0;j<c;j++){
			matrix[i][j]=paso[k];
			k++;
		}
		
	}

}
