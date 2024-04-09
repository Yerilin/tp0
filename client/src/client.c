#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
	

	log_info(logger,"Hola! Soy un Log\n");
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */
	
	config = iniciar_config();
	
	ip=config_get_string_value(config,"IP");
	puerto=config_get_string_value(config,"PUERTO");
	valor=config_get_string_value(config,"CLAVE");

	log_info(logger,"Se leyo el IP:%s, el PUERTO:%s, y la CLAVE:%s\n",ip,puerto,valor);

	

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config


	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor,conexion);

	// Armamos y enviamos el paquete

	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	nuevo_logger=log_create("tp0.log","TP0",1,LOG_LEVEL_INFO);
	if(nuevo_logger==NULL){
		printf("No se pudo iniciar un logger\n");
		exit(1);
	}

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	nuevo_config=config_create("cliente.config");
	if(nuevo_config==NULL){
		printf("No se pudo crear config\n");
		exit(1);
	}
	return nuevo_config;

}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	while(1){
		leido = readline("> ");
		int resultado;
		resultado=strcmp(leido,"");

		if(leido!=NULL && resultado!=0){

			log_info(logger,"Se leyo: %s\n",leido);
			free(leido);

		}
		if(resultado==0){
			free(leido);
			break;
		}

		
	}




	// El resto, las vamos leyendo y logueando hasta recibir un string vacío


	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete=crear_paquete();

	leido=readline(">");
	while(strcmp(leido,"")!=0){

		agregar_a_paquete(paquete,leido,string_length(leido)+1);
		free(leido);
		leido=readline(">");
	}
	free(leido);

	// Leemos y esta vez agregamos las lineas al paquete

	enviar_paquete(paquete,conexion);
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	eliminar_paquete(paquete);
} 

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
