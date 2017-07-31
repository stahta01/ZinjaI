### Panel *�rbol de Proyecto* � *�rbol de Archivos*

El panel de *�rbol de Proyecto*, o tambi�n llamado *�rbol de Archivos* muestra las archivos asociados al proyecto actual (en caso de haber un proyecto cargado), o todos los archivos abiertos (en caso de trabajar en modo programas simples, sin proyecto).

![](project_tree.png)


#### Categor�as
Las categor�as que pueden aparecer en el �rbol son:

*  **Fuentes** Archivos "compilables". Es decir, archivos que generar�n un objeto o binario. Usualmente estar�n aqu� todos los fuentes de C y C++. Se determina que un archivo es *fuente* por su extensi�n. La extensi�n v�lida para C es: **.c**, y las extensiones v�lidas para C++ son: **.cpp**, **.c++**, **.cc** y **.cxx**.
*  **Cabeceras** Archivos de cabecera (a incluir en fuentes con la directiva "#include"). Los archivos en esta categor�a ser�n parseados para detectar s�mbolos (clases, funciones, etc para el autcompletado) y tendr�n el coloreado de sintaxis habilitada, pero nunca ser�n compilados directamente (sino a trav�s de un #include en un fuente). Las extensiones v�lidas como cabeceras C/C++ son: **.h**, **.hh**, **.hpp**, **.hxx** y **.h++**.
*  **Otros** Aqu� estar�n todos los dem�s archivos abiertos/del proyecto (los que no caigan en ninguna de las categor�as anteriores). Estos archivos no participar�n del �rbol de s�mbolos ni tendr�n el coloreado de sintaxis C/C++ habilitado por defecto. Sin embargo, para algunos formatos conocidos (como Makefiles, o scripts de bash .sh), se habilitar� un coloreado simple alternativo. Para los dem�s archivos, el coloreado C/C++ se puede habilitar desde el [men� Ver](menu_ver#colorear_sintaxis.html).
*  **Lista Negra** Esta categor�a puede aparecer solo cuando se trabaja en modo proyecto y se utiliza el mecanismo de [Herencia de Proyectos](project_inheritance.html). A esta categor�a se mueven los archivos del proyecto padre que se quiere evitar heredar en el proyecto hijo (es decir que constituye una lista de excepciones).

En modo programa simple la categor�a de un archivo se define por su extensi�n y no es posible modificarla. En modo proyecto, se puede mover un archivo de una categor�a a otra utilizando el men� contextual.

En modo proyecto, adem�s, los items correspondientes a archivos heredados de otros .zprs que no hayan sido reasignados al proyecto actual como propios se identificar�n por estar presentados con un color de texto semi-transparente (en general, si el fondo del �rbol es blanco, se ver�n en gris en lugar de negro).



#### Men� contextual

Cuando se trabaja sobre un proyecto, el men� contextual del �rbol (click derecho sobre un archivo, o sobre una categor�a) es m�s completo y permite por ejemplo:

*  Mover los archivos de una categor�a a otra
*  Definir cuales ignorar para el autocompletado/�rbol de s�mbolos
*  Definir cuales abrir en modo solo-lectura
*  Definir un conjunto de opciones de compilaci�n diferentes al resto (a las establecidas en el cuadro de [Opciones de Compilaci�n y Ejecuci�n del Proyecto](project_config.html), para m�s detalle ver [Opciones de Compilaci�n por fuente](by_src_comp_args.html)).
*  Recompilar solo un fuente en particular; o moverlo a la primera posici�n en el orden de compilaci�n (para que sea el primero a compilar cada vez que se recompila todo el proyecto).
*  Renombrar el archivo.
*  Quitarlo del proyecto (y opcionalmente eliminarlo del disco).
*  Ver sus propiedades, o abrir el explorador de archivos (tanto el panel de *ZinjaI* como el del sistema) en la carpeta del mismo.
*  Modificar la visualizaci�n del �rbol para que muestre solo los nombres de archivos, o todas las rutas relativas a la carpeta del proyecto.
*  Abrir todos los archivos de una determinada categor�a.
*  Acceder a cuadros de di�logo para buscar archivos dentro del proyecto, o para a�adir uno o m�s (resultados de una b�squeda en el disco) archivos al proyecto (para esto hacer click derecho sobre alguna de las categor�as).
