### Sobre el manejo de Proyectos en ZinjaI...

Si bien *ZinjaI* se desarroll� inicialmente con la simplicidad como uno de los requerimientos m�s importantes, prevee tambi�n su utilizaci�n para el desarrollo de proyectos de mayor complejidad. Prueba de ello es el hecho de que el mismo *ZinjaI* es utilizado para su propio desarrollo (cada versi�n se utiliza para desarrollar la siguiente). El manejo de proyectos surge como una forma de dar al usuario mayor potencia y flexibilidad, sin perder la posibilidad de realizar un ejercicio o programa simple r�pidamente. Por esto, los programas simples se compilan en una sola linea sin necesidad de configurar absolutamente nada ni de incluirlos en ningun proyecto (solo abrir/escribir y compilar), mientras que la creaci�n de un proyecto requiere algunos pasos adicionales, pero presenta las siguientes ventajas:

<A name="config"/>
#### Configuraci�n de Proyecto

La configuraci�n del proyecto es mucho m�s extensa y especializada que la configuraci�n de un programa simple. Esta incluye diferentes opciones generales, opciones relacionadas a la integraci�n con herramientas externas, y opciones relacionadas a la compilaci�n, el enlazado y la ejecuci�n del mismo. Dichas opciones se encuentran distribuidas entre diferentes cuadros de di�logo, siendo los principales el de [Opciones Generales del Proyecto](project_general_config.html) y el de [Opciones de Compilaci�n y Ejecuci�n del Proyecto](project_config.html).

Respecto a las opciones de compilaci�n, enlazado y ejecuci�n, en un proyecto se pueden especificar m�s de una configuraci�n. Se denomina "perfil" a cada configuraci�n. Esto permite definir, como usualmente se hace en muchos otros IDEs, un perfil para utilizar durante el desarrollo (modo *Debug*) y otro diferente para generar el ejecutable final (modo *Release*). Sin embargo, la cantidad de perfiles es arbitraria, por lo que no debe limitarse solo a dos, pudiendo as� armar configuraciones seg�n diferentes criterios (Release/Debug, Sistema Operativo, Versi�n de las bibliotecas externas, etc).


<A name="portability"/>
#### Portabilidad del Proyecto

La portabilidad de un proyecto es una de los aspectos m�s cuidados en el manejo interno del mismo. Por portabilidad se refiere a la posibilidad de simplemente copiar la carpeta del mismo y abrirlo en otra PC (con igual o diferente sistema operativo, actualmente *Win32* y *GNU/Linux*) y poder editarlo y compilarlo con la menor cantidad de cambios posibles, o en muchos casos sin ning�n tipo de modificaci�n. Adem�s de poder generar diferentes configuraciones para diferentes sistemas operativos, *ZinjaI* realiza internamente otras adaptaciones requeridas tales como:

*  la capacidad de detectar y reemplazar autom�ticamente el caracter de separaci�n en las rutas de archivos
*  la capacidad de tomar indistantemente los caracteres de fin de linea utilizados por uno u otro sistema operativo
*  la inclusi�n de configuraciones para ambas plataformas en los proyecto plantilla incluidos
*  las consideraciones especiales en la generaci�n de *Makefiles* (ver [Di�logo Generar Makefile](makefile.html))
*  las consideraciones necesarias al construir los comandos de compilaci�n y ejecuci�n
*  la elecci�n de un compilador, depurador y dem�s herramientas necesarias disponibles gratuitamente para un gran n�mero de arquitecturas (gcc,gdb,etc)
*  la relativizaci�n de todos los paths de archivos pertenecientes al proyecto (todas las rutas se almacenan de forma relativa a la carpeta del proyecto siempre que se pueda)
*  la utilizaci�n en su desarrollo de un lenguaje C++ estandar y librer�as portables de gran aceptaci�n (como *wxWidgets*)
*  etc.


<A name="templates"/>
#### Utilizaci�n de Plantillas de Proyecto

*ZinjaI* permite crear un nuevo proyecto a partir de una plantilla. Cualquier subdirectorio que se encuentre en el directorio de plantillas (ver <A href="preferences.html">Di�logo de Preferencias</A>) ser� tomado como plantilla de proyecto. Crear un proyecto a partir de una plantilla implica copiar el contenido de la carpeta del proyecto plantilla a la carpeta del nuevo proyecto. Este contenido puede incluir archivos fuentes, cabeceras u otros incluidos en el proyecto, todas las configuraciones del mismo, etc. Para crear una nueva plantilla, simplemente cree un nuevo proyecto y copie el directorio correspondiente al directorio de plantillas (puede que deba reiniciar *ZinjaI* luego). Se incluyen alguna plantillas de ejemplo (proyecto que utilice las librer�as *wxWidgets*, y proyecto que utilice *OpenGL*).


#### Temas relacionados

*  [Secuencia de compilaci�n de un proyecto](project_building_sequence.html)
*  [Toolchains alternativos](toolchains.html)
*  [Creaci�n de bibliotecas](libs_generation.html)
*  [Herencia de archivos entres proyectos](project_inheritance.html)
