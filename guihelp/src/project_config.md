### Di�logo *Opciones de Compilaci�n y Ejecuci�n de Proyecto*

Este di�logo permite gestionar los perfiles de compilaci�n y ejecuci�n de un proyecto. Se accede al mismo a trav�z del comando [Opciones](menu_ejecucion.html#opciones) del [men� Ejecuci�n](menu_ejecucion.html). Si necesita configurar otras opciones no relacionadas a la compilaci�n y ejecuci�n (como tabulado, nombre, indices de autocompletado, archivo de macros de depuraci�n, etc.), utilice el di�logo de [Configuraci�n de Proyecto](project_general_config.html).

En cada proyecto se pueden definir uno o m�s perfiles (por ejemplo, uno para depuraci�n/debug y otro para produccion/release, o uno por plataforma, etc.). Cada perfil define aspectos relativos a la compilaci�n, el enlazado y la ejecuci�n del proyecto. Es decir, cuando se compila o ejecuta el proyecto, los pasos necesarios para dicha compilaci�n, las opciones que reciben el compilador y el enlazador, y la forma en que este resultado es ejecutado dependen del perfil activo en ese momento.


<A name="administracion"></A>
#### Administraci�n perfiles

Para administrar los diferentes perfiles debe utilizar los botones y la lista desplegable de la parte superior de la ventana: 

![](project_config_header.png)

*  **A�adir un nueva perfil**: para agregar un nuevo perfil debe utilizar el bot�n *Nuevo*. Cuando presione dicho bot�n se le pedir� un nombre para el nuevo perfil, a continuaci�n se le permitir� elegir otro perfil preexistente desde el cual copiar la configuraci�n inicial, y finalmente se crear� el mismo a�adiendose a la lista desplegable.

*  **Utilizar/activar un perfil**: para utilizar un perfil debe seleccionarlo y hacer click sobre el bot�n *Utilizar*. N�tese que el echo de seleccionar un perfil de la lista desplegable no lo convierte en el perfil activo para las siguientes compilaciones/ejecuciones, sino que solamente muestra su configuraci�n en las pesta�as para permitirle modificarlo.

*  **Renombrar un perfil existente**: para cambiarle el nombre a una configuraci�n seleccione la misma en la lista desplegable y presione *Renombrar*.

*  **Modificar un perfil existente**: para modificar el contenido de una configuraci�n existente debe seleccionarla en la lista desplegable, modificar los que desee.

*  **Eliminar un perfil**: para eliminar una configuraci�n seleccione la misma en la lista desplegable y presione *Eliminar*.

*Nota:* Existe una forma m�s r�pida de cambiar el perfil activo sin utilizar este cuadro de di�logo, que consiste en hacer click derecho sobre el bot�n de la barra de herramientas de la ventana principal que corresponde a este di�logo. Esta acci�n despliega un men� contextual con la lista de perfiles disponibles.


A continuaci�n se detallan las opciones que se pueden definir dentro de cada perfil:


<A name="general"></A>
#### Pesta�a General

Define opciones generales y de ejecuci�n del proyecto.

![](project_config_general.png)

*  **Ubicacion del ejecutable**: nombre o ubicaci�n y nombre del ejecutable. Esta ruta puede ser absoluta, relativa al directorio del proyecto. Puede utilizar adem�s la variable `${TEMP_DIR}` para referirse al directorio definido para temporales en la pesta�a *Compilaci�n*.

*  **Mecanismo de ejecuci�n**: permite elegir c�mo se ejecutar� el proyecto, para realizar tareas de inicializaci�n antes de lanzar el ejecutable, o lanzarlo de formas especiales:

    *  Regular: se lanza el ejecutable definido en el campo *Ubicaci�n del ejecutable* utilizando los argumentos definidos en el campo *Argumentos para la ejecuci�n*-

    *  Con Inicializaci�n: primero se ejecuta un script (con `/bin/sh` en GNU/Linux, o el int�rprete de comandos de Windows en Windows), y luego se procede como el caso Regular (se lanza el ejecutable configurado en el proyecto).

    *  Mediante wrapper: Se antepone al comando de ejecuci�n regular (ejecutable + argumentos) el comando que se ingrese en el campo de texto *comando wrapper*. Este comando recibir� como argumentos al ejecutable del proyecto y los argumentos regulares para el mismo, y deber� encargarse de lanzar la ejecuci�n (esto permite utilizar herramientas como `time` (de GNU/Linux) para instrumentar la ejecuci�n).

    *  Solo Script: en este caso ZinjaI nunca ejecuta el ejecutable generado, sino que solo lanza un script, y el script debe ser quien realice la ejecuci�n. El script puede utilizar algunas de las configuraciones definidas en el perfil, ya que las recibe como variables de entorno. En particular la variable `Z_PROJECT_PATH` contendr� la carpeta del proyecto, la variable `Z_PROJECT_BIN` contendr� la ubicaci�n del ejecutable, la variable `Z_ARGS` contendr� los argumentos para la ejecuci�n, y la variable `Z_TEMP_DIR` contedr� la ruta del directorio de temporales. El directorio de trabajo del script ser� el configurado en el campo *Directorio de trabajo*, y recibir� los argumentos definidos en *Argumentos para la ejecuci�n*.


*  **Script para ejecuci�n/comando wrapper**: indica el script (ruta completa o relativa a la carpeta del proyecto) del script que se utiliza cuando el mencanismo de ejecucion seleccionado esa *Con Inicializaci�n* o *Solo Script*; o el comando que se utiliza para lanzar la ejecuci�n a modo de wrapper cuando el mecanismo seleccionado es *Mediante wrapper*.

*  **Directorio de trabajo**: directorio en cual se ejecutar� el programa (o script).

*  **Siempre pedir argumentos al ejecutar**: si esta opci�n est� activada *ZinjaI* solicitar� los argumantos que debe pasarle al ejecutable antes de cada ejecuci�n.

*  **Argumentos para la ejecucion**: argumentos que debe recibir el ejecutable (o script) del proyecto para su ejecuci�n.

*  **Esperar una tecla luego de la ejecucion**: permite definir si *ZinjaI* esperar� a que se presione *Enter* luego de ejecutar su programa para evitar que la ventana del mismo se cierre inmediatamente sin poder ver los resultados. La opci�n "En caso de error" utiliza el valor de retorno del programa y solo espera si este es distinto de 0. Esta configuraci�n no aplica para los proyectos que no muestren consola (ver �tem "Es un proyecto de Consola" de la pesta�a "Enlazado" de este mismo cuadro de di�logo), ni para las ejecuciones en modo depuraci�n.

*  **Variables de entorno**: Permite modificar variables de entorno antes de ejecutar el proyecto. Colocando "NOMBRE=VALOR" se le asigna VALOR a la variable NOMBRE. Colocando NOMBRE+=VALOR el VALOR se le agrega al contenido previo de la variable NOMBRE. Puede colocar una lista de asignaciones separadas por espacios o comas, y puede utilizar comillas o caracteres de escape para introducir espacios, comillas, barras, etc, en VALOR. Al ejecutar un proyecto, el mismo hereda el ambiente (conjunto de variables de entorno de ZinjaI). El ambiente de ZinjaI se corresponde al heredado desde el sistema operativo, con el agregado en la variable PATH de la carpeta que contiene los ejecutables del compilador en el caso de Windows, y las carpetas de bibliotecas din�micas que el proyecto genere en las variables PATH o LD_LIBRARY_PATH (seg�n el sistema operativo). Las variables aqu� definidas se agregan o reemplazan en este ambiente previo.

	
<A name="compilacion"></A>
#### Pesta�a Compilacion

Define los parametros que se utilizan para la compilaci�n.

![](project_config_compiling.png)

*  **Parametros extra para la compilacion**: aqu� el usuario puede establecer libremente par�metros adicionales que *ZinjaI* utilizar� para la compilaci�n. Vea [Ayuda del compilador utilizado](gcc_index.html).

*  **Macros a definir**: permite ingresar una lista de macros de preprocesador (equivalentes a las definidas con #define en el c�digo fuente) que ser�n utilizadas para la compilaci�n de los fuentes (con el par�metro -D en gcc). El formato de ingreso es una lista separada por comas o espacios con los nombres y opcionalmente pegado el signo igual y el valor para dicha macro.

*  **Directorios adicionales para buscar cabeceras**: permite definir uno o m�s directorios en los que el compilador debe buscar los archivos de cabecera incluidos en los fuentes. Los directorios de la lista pueden estar separados por coma, punto y coma o espacios y pueden ser absolutos o relativos al directorio del proyecto. Si desea agregar una ruta que contenga espacios puede encerrarla entre comillas dobles. Equivale a la utilizaci�n del par�metro "-I".

*  **Estandar**: Permite elegir la versi�n del lenguaje C o C++ a utilizar (para especificar a gcc/g++ con el argumento -std=...). Elegir un est�ndar garantiza que el compilador cumple al menos con sus reglas, pero puede incluir extensiones. La casilla **estricto** permite desactivar las extensiones y limitarlo solo al est�ndar seleccionado (generando un error al querer utilizar alguna extensi�n, equivale al par�metro "-pedantic"). Los est�ndares "c++11" y "gnu++11" no est�n presentes en versiones de g++ menores a 4.7. Si ZinjaI detecta un versi�n menor a 4.7 los reemplazar� por "c++0x" y "gnu++0x", por lo que el soporte para estos est�ndares podr�a ser incompleto en esos casos. Si se elige la opci�n predeterminada, *ZinjaI* no indicar� a gcc/g++ qu� versi�n utilizar. Los valores predeterminados hasta gcc 4.8 son gnu90 y gnu++98(equivalente a gnu++03), pero podr�an cambiar en el futuro.

*  **Nivel de advertencias**: define la cantidad y el tipo de advertencias/avisos que el compilador arrojar� durante la compilaci�n. Los niveles "Ninguna" y "Todas" equivalen a los par�metros -"w" y "-wAll" respectivamente. El nivel predeterminado no necesita ning�n par�metro, ya que es el nivel predeterminado del compilador.

*  **Informaci�n de depuracion**: determnia si el compilador incluye o no informaci�n de depuraci�n en el ejecutable. Esta informaci�n es la que le permite al depurador reconocer qu� linea de c�digo se estaba ejecutando en determinado momento, la ubicaci�n de las variables para evaluar sus expresiones, etc. Equivale a los par�metros "-g0", "-g1", "-g2" y "-g3". El nivel m�s comunmente utilizado para la depuraci�n es el 2.

*  **Nivel de optimizacion**: determina las optimizaciones que el compilador realiza durante la compilaci�n. Estas optimizaciones permiten que el programa corra m�s r�pidamente u ocupe menos espacio en disco. Equivale a los par�metros "-O0", "-O1", "-O2", "-O3" y "-Os". El nivel 2 es el m�s utilizado comunmente para producci�n. Nota: estas optimizaciones alteran a veces el flujo de control interno del programa, o eliminan determinadas instrucciones, por lo que no deber�a utilizarse cuando se pretende depurar el programa, ya que lo observado en el depurador puede no condecirse exactamente con lo escrito en el c�digo fuente. Desde la versi�n 4.8 existe un nuevo nivel dise�ado para depuraci�n ("-Og"). Si selecciona esta opci�n pero su compilador no la soporta, ZinjaI lo reemplazar� por "-O0".

*  **Directorio para archivos temporales e intermedios**: ubicaci�n donde *ZinjaI* guardar� los archivos intermedios de la compilaci�n (objetos, archivos de extensi�n .o, uno por cada fuente compilable del proyecto). El �ltimo directorio esta ruta puede no existir, en cuyo caso ser� creado durante la primer compilaci�n. Esta ruta puede ser absoluta o relativa al directorio del proyecto.


<A name="enlazado"></A>
#### Pesta�a Enlazado

Define los parametros que se utilizan para el enlazado.

![](project_config_linking.png)

*  **Parametros extra para el enlazado**: aqu� el usuario puede establecer libremente par�metros adicionales que *ZinjaI* utilizar� para el enlazado. Vea [Ayuda del compilador utilizado](gcc_index.html)</A>.

*  **Directorios adicionales para buscar librerias**: permite definir uno o m�s directorios en los que el enlazador debe buscar los archivos de objetos de las librer�as externas. Los directorios de la lista pueden estar separados por coma, punto y coma o espacios y pueden ser absolutos o relativos al directorio del proyecto. Si desea agregar una ruta que contenga espacios puede encerrarla entre comillas dobles. Equivale a la utilizaci�n del par�metro "-L".

*  **Bibliotecas a enlazar**: define una lista de librerias externas a enlazar con los objetos del proyecto para crear el ejecutable. Los nombres de las librer�as puede estar separados por coma, punto y coma, o espacios. Si desea incluir un nombre que contenga espacios puede encerrarlo entre comillas dobles ("nombre de archivo"). Equivale a la utilizaci�n del par�metro "-l".

*  **"Stripear" el ejecutable**: esta opci�n extrae toda la informaci�n de depuraci�n del ejecutable final luego del enlazado. De esta forma, se obtiene un ejecutable m�s peque�o. Equivale al par�metro "-s". Notar que aunque se haya definido que el compilador no debe incluir informaci�n de depuraci�n al ejecutar, puede que alguna de las librer�as enlazadas s� la contenga, por lo que esta opci�n resulta especialmente �til en este caso.

*  **Es un programa de consola**: esta opci�n s�lo tiene sentido en windows y determina si el programa generado utilza o no una consola. Si est� desactivado se utiliza el par�metro "-mwindows"; lo cual permite ocultar la ventana negra si el programa crea su propia ventana. En sistemas Linux esta opci�n determina si al ejecutar el projecto *ZinjaI* muestra o no la ventana de la consola (*runner*); sin embargo esto no cambia el ejecutable, ya que linux no se hace distinci�n entre programas de consolas y programas de ventanas.

*  **Reenlazar obligatoriamente en la proxima compilacion/ejecucion**: si se selecciona esta opci�n el *ZinjaI* reenlazar� el ejecutable antes de la pr�xima ejecuci�n aunque no se detecten cambios en sus fuente u objetos. Luego de reenlazar el proyecto, esta opci�n de desactiva autom�ticamente. Puede ser �til cuando un cambio en alguno de los par�metros de enlazado lo amerite.

*  **Icono del ejecutable**: ruta completa o relativa a la carpeta de proyecto del archivo que se utilizar� como �cono del ejecutable al compilar en *Microsoft Windows*. Este icono se compila mediante un archivo de recursos generado autom�ticamente en la carpeta de archivos temporales del proyecto.

*  **Archivo manifest.xml**: ruta completa o relativa a la carpeta de proyecto del archivo que se utilizar� como manifest para en *Microsoft Windows*. Este archivo se compila mediante un archivo de recursos generado autom�ticamente en la carpeta de archivos temporales del proyecto.


<A name="secuencia"></A>
#### Pesta�a Secuencia

![](project_config_sequence.png)

Permite utilizar un [toolchain alternativo](toolchains.html), o alterar el proceso de construcci�n del proyecto insertando pasos adicionales. El proceso detallado, junto con las reglas que determinan cuando ejecutar estos pasos, se explica en la secci�n [Secuencia de contrucci�n de proyectos](project_building_sequence.html). Estos pasos se utilizan, por ejemplo, para insertar llamadas a parsers de bibioteca espec�ficas, compilaci�n de recursos adicionales, etc. Cuando agregue o modifique un paso personalizado, lo har� mediante el [Di�logo Agregar/Editar Paso de Compilaci�n Personalizado](compile_extra_steps.html). Consulte este enlace para encontrar una descripci�n m�s detallada de las propiedades de cada paso.


<A name="biblioteca"></A>
#### Pesta�a Biblioteca

![](project_config_libraries.png)

Permite definir bibliotecas que ser�n generadas a partir de un subconjunto de fuentes del proyectos. Estas bibliotecas ser�n adem�s enlazadas con el ejecutable final. Para generar una biblioteca, debe agregarla en esta lista y definir sus propiedades, y qu� fuentes la componen, mediante el [Di�logo Generar Biblioteca](lib_to_build.html). Para comprender detalladamente la forma de compilaci�n de las bibliotecas y c�mo se integran en el proyecto consulte la secci�n [Secuencia de contrucci�n de proyectos](project_building_sequence.html).
Por �ltimo, si el objetivo de su proyecto es s�lamente construir una o varias bibliotecas, pero no un ejecutable, puede tildar la casilla "Generar solo bibliotecas". Esto evita que *ZinjaI* intente enlazar un ejecutable final.
