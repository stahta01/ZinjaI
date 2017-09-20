#### GDB on Mac OS X

El depurador por defecto en los sistemas Mac OS modernos es lldb. Sin embargo, *ZinjaI* solo est� preparado para interactuar con gdb.

Suponiendo que el sistema en el que se encuentra ya tiene correctamente instalado un compilador (gcc o llvm-clang, usualmente instalados a trav�s de XCode), *ZinjaI* puede automatizarle la descarga y compilaci�n del depurador.

Sin embargo, se requiere firmar digitalmente al ejecutable del depurador para que el sistema le otorgue los permisos necesarios para controlar a los programas a depurar. Lamentablemente, el proceso de generaci�n de la firma necesaria no es simple y no est� automatizado. 

A continuaci�n se describen los pasos necesarios para instalar gdb y firmarlo adecuadamente con la ayuda de *ZinjaI*:

 1. Al iniciar ZinjaI, si el depurador no se encuentra instalado, se generar� un mensaje de advertencia inform�ndole tal situaci�n, y se le ofrecer� (mediante un checkbox en el mismo mensaje) la descarga e instalaci�n autom�tica. Si el mensaje no aparece, puede lanzar el proceso nuevamente mediante [este enlace](action:gdb_on_mac).
 
 2. El script comenzar� a descargar y compilar gdb (necesitar� conexi�n a Internet si es la primera vez que lo ejecuta).
 
 3. Mientras tanto, puede comenzar a generar una llave adecuada para firmar gdb. Utilice [este enlace](action:keychain_access) para abrir el cuadro de configuraci�n de "Accesso a Llaves" de sus sistema y siga las siguientes instrucciones:
    1. En el panel de la izquierda de la ventana, seleccione "Inicio de sesi�n"
    2. Vaya al men� de la aplicaci�n (borde superior de la pantalla) y seleccione: "Acceso a llaveros" -> "Asistente para certificados" -> "Crear un ceritificado..."
    3. En el nuevo cuadro de di�logo, configure: "Nombre"->"zinjai-gdb", "Tipo de Identidad"->"Raiz auto-firmada", "Tipo de Certificado"->"Firma de Codigo"
    4. Click en "Crear", luego en "Continue", luego en "Ok" para finalizar el asistente.
    5. Click en "Mis certificados" en un de los paneles de la izquierda.
    6. En la lista principal de la ventana, doble click en el nuevo certificado: "zinjai-gdb"
    7. Despliegue la secci�n "Confiar" con un click en el triangulo, busque "Firma de codigo" y seleccione "Confiar siempre". Luego deber� autenticarse con huella digital y/o password para confirmar el cambio.
    8. Arrastre el nuevo certificado "zinjai-gdb" desde "Inicio de sesi�n" hacia "Sistema" en el panel de la izquierda. Tendr� que volver a autenticarse una o dos veces. En una de ellas, cuando tenga la oportunidad, seleccione "Permitir siempre".
    9. Arrastre el nuevo certificado desde la ventana de "Acceso a llaves" hacia el escritorio del sistema. 
    9. Vaya a la terminal lanzada en el paso 1, y cuando la compilaci�n finalice y el script se lo pida, presione enter una vez.
    10. En la ventana de acceso a llaves, arrastar "zinjai-gdb" nuevamente a "inicio de sesi�n". 
    10. Finalmente puede cerrar esa ventana, y presionar enter una vez m�s en la consola del paso 1.
 
 4. Luego de que finalice la descarga y compilaci�n de gdb del paso 2, y la generaci�n y aplicaci�n del nuevo certificado del paso 3, zinjai intentar� reiniciar el servicio que gestiona estos accesos. En caso de que este �ltimo paso falle, deber� reiniciar su sistema para que los cambios tengan efecto.

Si el proceso falla, igual puede utilizar ZinjaI para editar el c�digo, compilar, y ejecutar sus programas. Pero no podr� utilizar las funcionalidades del men� "Depuraci�n".
