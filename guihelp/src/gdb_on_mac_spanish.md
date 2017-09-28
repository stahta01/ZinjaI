#### Instalaci�n de GDB en Mac OS

El depurador por defecto en los sistemas Mac OS modernos es lldb. Sin embargo, *ZinjaI* solo est� preparado para interactuar con gdb.

Suponiendo que el sistema en el que se encuentra ya tiene correctamente instalado un compilador (gcc o llvm-clang, usualmente instalados a trav�s de XCode), *ZinjaI* puede automatizarle la descarga y compilaci�n del depurador.

Sin embargo, se requiere firmar digitalmente al ejecutable del depurador para que el sistema le otorgue los permisos necesarios para controlar a los programas a depurar. Lamentablemente, el proceso de generaci�n de la firma necesaria no es simple y no est� automatizado. 

A continuaci�n se describen los pasos necesarios para instalar gdb y firmarlo adecuadamente con la ayuda de *ZinjaI*:

 1. Lanzar el proceso de descarga y compilaci�n mediante [este enlace](action:gdb_on_mac) (necesitar� conexi�n a Internet si es la primera vez que lo ejecuta).
 
 2. Mientras tanto, utilice [este enlace](action:keychain_access) para abrir el cuadro de configuraci�n de *Accesso a Llaves* de sus sistema y siga las siguientes instrucciones:
    1. En el panel de la izquierda de la ventana, seleccione *Inicio de sesi�n*
    2. Vaya al men� de la aplicaci�n (borde superior de la pantalla) y seleccione: *Acceso a llaveros* -> *Asistente para certificados* -> *Crear un ceritificado...*
    3. En el nuevo cuadro de di�logo, configure: *Nombre*->*zinjai-gdb*, *Tipo de Identidad*->*Raiz auto-firmada*, *Tipo de Certificado*->*Firma de Codigo*
    4. Click en *Crear*, luego en *Continuar*, luego en *Aceptar* para finalizar el asistente.
    5. Click en *Mis certificados* en un de los paneles de la izquierda.
    6. En la lista principal de la ventana, doble click en el nuevo certificado: *zinjai-gdb*
    7. Despliegue la secci�n *Confiar* con un click en el triangulo, busque *Firma de codigo* y seleccione *Confiar siempre*. Luego deber� autenticarse con huella digital y/o password para confirmar el cambio.
    8. Arrastre el nuevo certificado *zinjai-gdb* desde *Inicio de sesi�n* hacia *Sistema* en el panel de la izquierda. Tendr� que volver a autenticarse una o dos veces. En una de ellas, cuando tenga la oportunidad, seleccione *Permitir siempre* y *Confiar Siempre*.
    9. Seleccion *Sistema*, y arrastre el nuevo certificado desde la ventana de *Acceso a llaves* hacia el escritorio. 
    10. Vaya a la terminal lanzada en el paso 1, y cuando la compilaci�n finalice y el script se lo pida, presione enter solo una vez.
    11. En la ventana de acceso a llaves, arrastar *zinjai-gdb* nuevamente a *inicio de sesi�n*. 
    12. Finalmente puede cerrar esa ventana, y presionar enter una vez m�s en la consola del paso 1 para concluir el proceso.
 
 3. Por �ltimo, *ZinjaI* intentar� reiniciar el servicio que gestiona estos accesos (en caso de que este �ltimo paso falle, deber� reiniciar su sistema para que los cambios tengan efecto).
 
Si completa este proceso con �xito, podr� comenzar a utilizar las funcionalidades de depuraci�n de ZinjaI. 
* Es normal que en la primer depuraci�n, el sistema le pida usuario y contrase�a. En las sisguientes ya no ser� necesario.
* Es normal que al ejecutar en depuraci�n vea en consola el mensaje *&"warning: GDB: Failed to set controlling terminal: Operation not permitted\n"*. Puede ignorar este mensaje.

Si el proceso falla, igual puede utilizar *ZinjaI* para editar el c�digo, compilar, y ejecutar sus programas. Pero no podr� utilizar las funcionalidades del men� *Depuraci�n*.


Instrucciones basadas en: [http://llvm.org/svn/llvm-project/lldb/trunk/docs/code-signing.txt](http://llvm.org/svn/llvm-project/lldb/trunk/docs/code-signing.txt)