#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "TPIntegrador.h"
typedef char palabra[60];
int password=123456;

struct fecha{
	int dia,mes,anio;
};

struct Usuario{
	char user[10],pass[32],ayn[60];
}user,user_aux;

struct Veterinario{
	int matricula,dni;
	char ayn[60],tel[25];
}vet,vet_aux;

struct Mascota{
	int  dni_duenio;
	char ayn[60],dom[60],local[60],tel[25];
	float peso;
	fecha fec_nac;
}pet,pet_aux;

struct Turno{
	int mat_vet,dni_duenio;
	char det_at[380];
	fecha fec;
}turn,turn_aux;

bool verificacion(FILE *Veterinarios, FILE *Usuarios,palabra usuario,palabra password,int band){
	bool resp;
	_flushall();
	rewind(Usuarios);
	rewind(Veterinarios);
	fread(&user,sizeof(user),1,Usuarios);
	do{
		if(strcmp(usuario,user.user)==0){
			if(strcmp(password,user.pass)==0){
				if(band == 1){
					fread(&vet,sizeof(vet),1,Veterinarios);
					do{
						if(strcmp(user.ayn,vet.ayn)==0){
							resp = true;
							break;
						}else{
							resp = false;
						}
						fread(&vet,sizeof(vet),1,Veterinarios);
					}while(!feof(Veterinarios));
					break;
				}else{
					resp = true;
					break;
				}
			}else{
				resp = false;
				printf("Contraseña Incorrecta\n");
			}
		}else{
			resp = false;
			printf("Usuario Incorrecto \n",usuario,user.user);
		}
		fread(&user,sizeof(user),1,Usuarios);
	}while(!feof(Usuarios));
	return resp;
}

void login(FILE *Veterinarios, FILE *Usuarios,bool &hab,int band){
	Veterinarios = fopen("Veterinarios.dat","r+b");
	Usuarios = fopen("Usuarios.dat","r+b");						
	palabra usuario,password;
	_flushall();
	printf("Bienvenido al Panel de Login.\nPor favor Ingrese los datos\n\nUsername: ");
	gets(usuario);
	printf("Password: ");
	gets(password);
	if(verificacion(Veterinarios,Usuarios,usuario,password,band)){
		hab=true;
	}else{
		printf("Usuario o Contraseña Incorrectos\n");
		system("pause");
	}
	fclose(Veterinarios);
	fclose(Usuarios);
}

bool condPass(palabra password){
	int mayus=0,minus=0,num=0,nrep=0;
	char B='\0',A='\0',N='\0';
	bool ok=false;
	if(strlen(password)>=6 and strlen(password)<=32){
		for(int i=0;i<strlen(password);i++){
			if((password[i]>='a' and password[i]<='z') or (password[i]>='A' and password[i]<='Z') or (password[i]>='0' and password[i]<='9')){
				if(password[i]>='A' and password[i]<='Z'){A=password[i];N='\0';mayus++;}
				if(password[i]>='a' and password[i]<='z'){A=password[i]-32;N='\0';minus++;}
				if(password[i]>='0' and password[i]<='9'){N=password[i];A='\0';num++;}
				if(N>='0' and N<='9' and B>='0' and B<='9'){
					nrep++;
				}
				if(nrep>=3){printfn("No puede tener mas de 3 digitos numericos consecutivos.\n");break;}
				if(B+1!=A){			
					if(mayus>=1){
						if(minus>=1){
							if(num>=1){
								ok=true;
							}else{
								if(i==strlen(password)-1)printfn("Debe tener al menos 1 caracter numerico.\n");
							}
						}else{
							if(i==strlen(password)-1)printfn("Debe tener al menos 1 caracter en minuscula.\n");
						}
					}else{
						if(i==strlen(password)-1)printfn("Debe tener al menos 1 caracter en mayuscula.\n");
					}
				}else{
					printfn("No puede tener caracteres consecutivos en orden ascendente A-Z.\n");
					break;
				}
				if(password[i]>='A' and password[i]<='Z')B=password[i];
				if(password[i]>='a' and password[i]<='z')B=password[i]-32;
				if(password[i]>='0' and password[i]<='9')B=password[i];
			}else{
				printfn("La contraseña debe ser alfanumerica.\n");
				break;
			}
		}
	}else{
		printfn("Debe tener una logitud entre 6 y 32 caracteres.\n");
	}
	return ok;
}

bool condUser(FILE *Usuario,palabra usuario){
	bool ok=false,cpl=false;
	int mayus=0,num=0;
	rewind(Usuario);
	if(strlen(usuario)>=6 and strlen(usuario)<=10){
		for(int i=0;i<strlen(usuario);i++){
			if((usuario[i]>='a' and usuario[i]<='z') or (usuario[i]>='A' and usuario[i]<='Z') or (usuario[i]>='0' and usuario[i]<='9') or (usuario[i]=='+' or usuario[i]=='-' or usuario[i]=='/' or usuario[i]=='*' or usuario[i]=='?' or usuario[i]=='¿' or usuario[i]=='!' or usuario[i]=='¡')){
				if(usuario[i]>='A' and usuario[i]<='Z')mayus++;
				if(usuario[i]>='0' and usuario[i]<='9')num++;
				if(usuario[0]>='a' and usuario[0]<='z'){
					if(mayus>=2){
						if(num<=3 and num>=1){
							if(i==strlen(usuario)-1){
								ok=true;
								cpl=true;	
							}
						}else{
							if(i==strlen(usuario)-1)printfn("Debe tener maximo 3 digitos numericos.\n");
						}
					}else{
						if(i==strlen(usuario)-1)printfn("Debe tener al menos 2 caracter en mayuscula.\n");
					}
				}else{
					printfn("Debe empezar con una letra minuscula.\n");
					break;
				}
			}else{
				printfn("El unico conjunto de simbolos permitidos es: (+,-,/,*,?,¿,!,¡)");
				break;
			}
		}
	}else{
		printfn("Debe tener una logitud entre 6 y 10 caracteres.\n");
	}
	_flushall();
	if(ok){
		fread(&user_aux,sizeof(user_aux),1,Usuario);
		do{
			if(strcmp(usuario,user_aux.user)==0){
				cpl=false;
				printfn("El usuario ingresado ya existe!.\n");
				break;
			}
			fread(&user_aux,sizeof(user_aux),1,Usuario);
		}while(!feof(Usuario));
	}
	return cpl;
}

void turnRegister(FILE *Turnos){
	char o;
	printf("Registro de Turno\n");
	printf("=======================\n");
	_flushall();
	printf("Matricula de Veterinario: ");
	scanf("%d",&turn.mat_vet);
	printf("\tFecha: \n============================\n");
	printf("Dia: ");
	scanf("%d",&turn.fec.dia);
	printf("Mes: ");
	scanf("%d",&turn.fec.mes);
	printf("Año: ");
	scanf("%d",&turn.fec.anio);
	printf("DNI del Dueño: ");
	scanf("%d",&turn.dni_duenio);
	_flushall();
	printf("Detalle de Atencion: ");
	gets(turn.det_at);
	system("cls");
	printf("Turno a registrar\n");
	printf("=======================\n");
	printf("Matricula de Veterinario: ");
	printf("%d\n",turn.mat_vet);
	printf("Fecha: ");
	printf("%d/%d/%d\n",turn.fec.dia,turn.fec.mes,turn.fec.anio);
	printf("DNI del Dueño: ");
	printf("%d\n",turn.dni_duenio);
	printf("Detalle de Atencion: ");
	printf("%s\n",turn.det_at);
	printf("Registrar usuario? (s/n): ");
	scanf("%c",&o);
	if(o=='s' or o=='S'){
		fseek(Turnos,0,SEEK_END);
		fwrite(&turn,sizeof(turn),1,Turnos);
	}
}

void petRegister(FILE *Mascotas){
	char o;
	printf("Registro de Mascota\n");
	printf("=======================\n");
	_flushall();
	printf("Apellido y Nombre: ");
	gets(pet.ayn);
	printf("Domicilio: ");
	gets(pet.dom);
	printf("DNI del Dueño: ");
	scanf("%d",&pet.dni_duenio);
	_flushall();
	printf("Localidad: ");
	gets(pet.local);
	printf("\tFecha de Nacimiento\n=====================================\n");
	printf("Dia: ");
	scanf("%d",&pet.fec_nac.dia);
	printf("Mes: ");
	scanf("%d",&pet.fec_nac.mes);
	printf("Año: ");
	scanf("%d",&pet.fec_nac.anio);
	printf("Peso: ");
	scanf("%f",&pet.peso);
	_flushall();
	printf("Telefono: ");
	gets(pet.tel);
	system("cls");
	printf("Mascota a registrar\n");
	printf("=======================\n");
	printf("Apellido y Nombre: ");
	printf("%s\n",pet.ayn);
	printf("Domicilio: ");
	printf("%s\n",pet.dom);
	printf("DNI del Dueño: ");
	printf("%d\n",pet.dni_duenio);
	printf("Localidad: ");
	printf("%s\n",pet.local);
	printf("Nacimiento: ");
	printf("%d/%d/%d\n",pet.fec_nac.dia,pet.fec_nac.mes,pet.fec_nac.anio);
	printf("Telefono: ");
	printf("%s\n",pet.tel);
	printf("Registrar usuario? (s/n): ");
	scanf("%c",&o);
	if(o=='s' or o=='S'){
		fseek(Mascotas,0,SEEK_END);
		fwrite(&pet,sizeof(pet),1,Mascotas);
	}
}

void vetRegister(FILE *Veterinarios, FILE *Usuarios){
	char o;
	printf("Registro de Veterinario\n");
	printf("=======================\n");
	_flushall();
	printf("Apellido y Nombre: ");
	gets(vet.ayn);
	strcpy(user.ayn,vet.ayn);
	printf("Matricula: ");
	scanf("%d",&vet.matricula);
	printf("DNI: ");
	scanf("%d",&vet.dni);
	_flushall();
	printf("Telefono: ");
	gets(vet.tel);
	printf("Usuario: ");
	gets(user.user);
	while(condUser(Usuarios,user.user)==false){
		printf("Usuario: ");
		gets(user.user);
	}
	printf("Constrasenia: ");
	gets(user.pass);
	while(condPass(user.pass)==false){
		printf("Constrasenia: ");
		gets(user.pass);
	}
	system("cls");
	printf("Veterinario a registrar\n");
	printf("=======================\n");
	printf("Apellido y Nombre: %s\n",vet.ayn);
	printf("Matricula: %d\n",vet.matricula);
	printf("DNI: %d\n",vet.dni);
	printf("Telefono: %s\n",vet.tel);
	printf("Usuario: %s\n",user.user);
	printf("Constrasenia: %s\n\n",user.pass);
	printf("Registrar usuario? (s/n): ");
	scanf("%c",&o);
	if(o=='s' or o=='S'){
		fseek(Veterinarios,0,SEEK_END);
		fwrite(&vet,sizeof(vet),1,Veterinarios);
		fwrite(&user,sizeof(user),1,Usuarios);
	}
}

void asistRegister(FILE *Usuarios){
	char o;
	printfn("Registro de Asistente\n");
	printfn("=======================\n");
	_flushall();
	printfn("Apellido y Nombre: ");
	gets(user.ayn);
	_flushall();
	printfn("Usuario: ");
	gets(user.user);
	while(condUser(Usuarios,user.user)==false){
		printf("Usuario: ");
		gets(user.user);
	}
	printfn("Constrasenia: ");
	gets(user.pass);
	while(condPass(user.pass)==false){
		printf("Constrasenia: ");
		gets(user.pass);
	}
	system("cls");
	printfn("Asistente a registrar\n");
	printfn("=======================\n");
	printfn("Apellido y Nombre: ");
	printf("%s\n",user.ayn);
	printf("Usuario: %s\n",user.user);
	printf("Constrasenia: %s\n\n",user.pass);
	printf("Registrar usuario? (s/n): ");
	scanf("%c",&o);
	if(o=='s' or o=='S'){
		fseek(Usuarios,0,SEEK_END);
		fwrite(&user,sizeof(user),1,Usuarios);
	}
}

bool admin(){
	int p;
	printfn("Ingrese la contraseña de administrador: ");
	scanf("%d",&p);
	if(p==password){
		printfn("\nIngreso de administrador exitoso!.\n\n");
		system("pause");
		return true;
	}else{
		printfn("\nLa contraseña ingresada es incorrecta.\n\n");
		system("pause");
		return false;
	}
}

bool succes(bool target, int mod){
	if(target == false and mod == 2){
		printfn("\nDebe estar registrado como Asistente del Veterinario o Veterinario.\nPor favor Inicie Sesion.\n\n");
		system("pause");
		return false;
	}else if(target == false and mod == 3){
		printfn("\nDebe estar registrado como Veterinario.\nPor favor Inicie Sesion.\n\n");
		system("pause");
		return false;
	}else{
		return target;
	}
}

void openFile(FILE *Archivo, const palabra nombre){
	bool H;
	do{
		H=true;
		Archivo = fopen(nombre,"r+b");
		if(Archivo==NULL){
			Archivo = fopen(nombre,"w+b");
			H=false;
			fclose(Archivo);
		}
	}while(H==false);
	fclose(Archivo);
}

void mod1(FILE *Veterinarios,FILE *Usuarios){
	int O;
	do{
		bool H=true;
		system("cls");
		printfn("Modulo Administracion\n");
		printfn("=========================\n");
		printfn("1.- Registrar Veterinario\n");
		printfn("2.- Registrar Usuario Asistente\n");
		printfn("3.- Atenciones por Veterinarios\n");
		printfn("4.- Ranking de Veterinarios por Atenciones\n\n");
		printfn("5.- Cerrar la aplicacion.\n\n");
		printfn("Ingrese una opcion: ");
		scanf("%d",&O);
		if(O>5 or O<1){
			printfn("\nLa opcion seleccionada es inexistente.\nPor favor Ingrese nuevamente la opcion.\n\n");
			system("pause");
			H=false;
		}
		if(H){
			switch(O){
				case 1:{
					openFile(Veterinarios,"Veterinarios.dat");
					openFile(Veterinarios,"Usuarios.dat");
					Veterinarios = fopen("Veterinarios.dat","r+b");
					Usuarios = fopen("Usuarios.dat","r+b");						
					vetRegister(Veterinarios,Usuarios);
					fclose(Veterinarios);
					fclose(Usuarios);
					break;
				}
				case 2:{
					openFile(Veterinarios,"Usuarios.dat");
					Usuarios = fopen("Usuarios.dat","r+b");	
					asistRegister(Usuarios);
					fclose(Usuarios);
					break;
				}
				case 3:{
					
					break;
				}
				case 4:{
					
					break;
				}
				case 5:{
					
					break;
				}
			}
		}
	}while(O!=5);
}

void mod2(bool &user_asist, FILE *Mascotas, FILE *Turnos,FILE *Veterinarios,FILE *Usuarios){
	int O;
	do{
		bool H=true;
		system("cls");
		printfn("Modulo del Asistente\n");
		printfn("=========================\n");
		printfn("1.- Iniciar Sesion\n");
		printfn("2.- Registrar Mascota\n");
		printfn("3.- Registrar Turno\n");
		printfn("4.- Listado de Atenciones por Veterinario y Fecha\n\n");
		printfn("5.- Cerrar la aplicacion.\n\n");
		printfn("Ingrese una opcion: ");
		scanf("%d",&O);
		if(O>5 or O<1){
			printfn("\nLa opcion seleccionada es inexistente.\nPor favor Ingrese nuevamente la opcion.\n\n");
			system("pause");
			H=false;
		}
		if(H){
			switch(O){
				case 1:{
					login(Veterinarios,Usuarios,user_asist,0);
					break;
				}
				case 2:{
					if(!succes(user_asist,2))break;
					openFile(Mascotas,"Mascotas.dat");
					Mascotas = fopen("Mascotas.dat","r+b");	
					petRegister(Mascotas);
					fclose(Mascotas);
					break;
				}
				case 3:{
					if(!succes(user_asist,2))break;
					openFile(Turnos,"Turnos.dat");
					Turnos = fopen("Turnos.dat","r+b");	
					turnRegister(Turnos);
					fclose(Turnos);
					break;
				}
				case 4:{
					if(!succes(user_asist,2))break;
					
					break;
				}
			}
		}
	}while(O!=5);
}

void mod3(bool &user_vet,FILE *Mascotas, FILE *Turnos,FILE *Veterinarios,FILE *Usuarios){
	int O;
	do{
		bool H=true;
		system("cls");
		printfn("Modulo Consultorio Veterinario\n");
		printfn("=========================\n");
		printfn("1.- Iniciar Sesion\n");
		printfn("2.- Visualizar Lista de Espera de Turnos (informe)\n");
		printfn("3.- Registrar Evolucion de la Mascota\n\n");
		printfn("4.- Cerrar la aplicacion.\n\n");
		printfn("Ingrese una opcion: ");
		scanf("%d",&O);
		if(O>4 or O<1){
			printfn("\nLa opcion seleccionada es inexistente.\nPor favor Ingrese nuevamente la opcion.\n\n");
			system("pause");
			H=false;
		}
		if(H){
			switch(O){
				case 1:{
					login(Veterinarios,Usuarios,user_vet,1);
					break;
				}
				case 2:{
					if(!succes(user_vet,3))break;
					
					break;
				}
				case 3:{
					if(!succes(user_vet,3))break;
					
					break;
				}
			}
		}
	}while(O!=4);
}

main(){
	FILE *Usuarios,*Veterinarios,*Mascotas,*Turnos;
	int O;
	bool user_asist=false,user_vet=false;
	setlocale(LC_ALL,"spanish");
	do{
		bool H=true;
		system("cls");
		printfn("Menu Principal\n");
		printfn("=========================\n");
		printfn("1.- Modulo Administracion\n");
		printfn("2.- Modulo del Asistente\n");
		printfn("3.- Modulo Consultorio Veterinario\n\n");
		printfn("4.- Cerrar la aplicacion.\n\n");
		printfn("Ingrese una opcion: ");
		scanf("%d",&O);
		if(O>4 or O<1){
			printfn("\nLa opcion seleccionada es inexistente.\nPor favor Ingrese nuevamente la opcion.\n\n");
			system("pause");
			H=false;
		}
		if(H){
			switch(O){
				case 1:{
					if(!admin())break;
					mod1(Veterinarios,Usuarios);
					break;
				}
				case 2:{
					if(user_vet)user_asist=user_vet;
					mod2(user_asist,Mascotas,Turnos,Veterinarios,Usuarios);
					break;
				}
				case 3: {
					mod3(user_vet,Mascotas,Turnos,Veterinarios,Usuarios);
					break;
				}
			}
		}
	}while(O!=4);
}
