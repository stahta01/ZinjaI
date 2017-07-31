### Di�logo *Configuraci�n de Proyecto*

Este di�logo presenta opciones generales de configuraci�n del proyecto, y da acceso r�pido a varias configuraciones relacionadas a herramientas externas. Para acceder al mismo se utiliza la opci�n [Configuraci�n de proyecto](menu_archivo.html#configuracion_proyecto) del men� [Configuraci�n de proyecto](menu_archivo.html).


<A name="general"></A>
#### General

En esta pesta�a encontrar� configuraciones generales propias de este cuadro de di�logo (es decir, que solo se pueden definir desde aqu�):

*  **Nombre del proyecto** Puede introducir aqu� cualquier cadena de texto. Este nombre ser� el que se muestre en la barra de t�tulo de *ZinjaI* mientras el proyecto est� abierto.

*  **Tabulado** Aqu� se define el tipo de tabulado que se utiliza al indentar el c�digo fuente, y eventualmente la representaci�n de los caracteres TAB. Los valores iniciales se heredan al crear un proyecto de los generales definidos en el [Cuadro de Preferencias](preferences.html#estilo) de *ZinjaI*, pero  luego permanecen asociados al proyecto y se utilizan cuando elmismo est� abierto reemplazando a los generales para que el proyecto reciba un tratamiento uniforma aunque se lo edite con diferentes instalaciones y configuraciones de *ZinjaI*.

*  **Extensiones preferidas** Aqu� se definen las extensiones por defecto para archivos fuente y cabecera. Estas extensiones se utilizar�n al crear archivos o clases desde la opci�n [Nuevo](menu_archivo.html#nuevo) del [Men� Archivo](menu_archivo.html).

*  **Heredar archivos de** Puede ingresar aqu� la ruta (preferentemente relativa) a uno o m�s archivos .zpr (de otros proyectos *ZinjaI*). Su proyecto actual heredar� (incluir� en su propio arbol de proyecto) todos los archivos (fuentes, cabeceras y otros) definidos en dichos proyectos. La lista de archivos heredados no es fija, sino que se actualiza (se releen los .zprs) cada vez que se abre el proyecto. M�s sobre la [Herencia de Proyectos](project_inheritance.html)...

*  **�ndices de autocompletado adicionales** Aqu� se pueden definir nombres de archivos de �ndices de autocompletado que en caso de no estar activados en las [preferencias generales](preferences.html#asistencias) (y de estar instalados en el sistema) se activar�n autom�ticamente al abrir el proyecto. Utilice esta opci�n para activar �ndices de bibliotecas no est�ndar que utilice en su proyecto.

*  **Archivo de definici�n de autoc�digos** Puede especificar aqu� un archivo de [autoc�digos](autocode.html) para reemplazar al definido en las [preferencias generales](preferences.html#asistencias) mientras se trabaja con el proyecto.

*  **Archivo de macros para gdb** Puede especificar aqu� un archivo de comandos gdb para reemplazar al definido en las [preferencias generales](preferences.html#depuracion) mientras se trabaja con el proyecto. Al iniciar el depurador, *ZinjaI* ejecuta en gdb este archivo antes de inciar la ejecuci�n del programa a depurar. Notar que si bien el nombre del campo sugiere que el archivo deber�a utilizarse para definir macros gdb, en realidad el archivo puede contener cualquier comando gdb v�lido que no implique iniciar la ejecuci�n.

*  **Mejora de inspecciones seg�n tipo** Puede definir aqu� plantillas adicionales a las definidas en las [preferencias generales](preferences.html#depuracion) para la mejora en la visualizaci�n de inspecciones. Puede aprovechar este cuadro para agregar mejoras propias de estructuras de datos espec�ficas de su proyecto, o de bibliotecas no est�ndar que su proyecto utilice.

<A name="mas"></A>
#### M�s

Esta pesta�a ofrece accesos a otros cuadros de di�logo configuraci�n del proyecto m�s espec�ficos. Los primeros relacionados a los perfiles de compilaci�n y sus opciones (accesibles desde el [men� Ejecuci�n](menu_ejecucion.html) y/o desde el men� contextual del [�rbol de Proyecto](panel_project_tree.html)), los siguientes relacionados a herramientas externas (accesibles desde los diferentes submen�es del [men� Herramientas](menu_herramientas.html)).


<A name="info"></A>
#### Info

Esta pesta�a no permite variar ninguna configuraci�n, sino que da acceso a algunas herramientas (ya presentes en el [men� Herramientas](menu_herramientas.html) que presentan informaci�n resumida/estad�stica del proyecto y sus archivos.
