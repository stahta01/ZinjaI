#### GDB on Mac OS X

El depurador por defecto en los sistemas Mac OS modernos es lldb. Sin embargo, *ZinjaI* solo est� preparado para interactuar con gdb.

Suponiendo que el sistema en el que se encuentra ya tiene correctamente instalado un compilador (gcc o llvm-clang, usualmente instalados a trav�s de XCode), *ZinjaI* puede automatizarle la descarga y compilaci�n del depurador.

Sin embargo, se requiere firmar digitalmente al ejecutable del depurador para que el sistema le otorgue los permisos necesarios para controlar a los programas a depurar. Lamentablemente, el proceso de generaci�n de la firma necesaria no es simple y no est� automatizado. 

A continuaci�n se describen los pasos necesarios para instalar gdb y firmarlo adecuadamente con la ayuda de *ZinjaI*:

 1. Al iniciar ZinjaI, si el depurador no se encuentra instalado, se generar� un mensaje de advertencia inform�ndole tal situaci�n, y se le ofrecer� (mediante un checkbox en el mismo mensaje) la descarga e instalaci�n autom�tica. Si el mensaje no aparece, puede lanzar el proceso nuevamente mediante [este enlace](action:gdb_on_mac).
 
 2. El script comenzar� a descargar y compilar gdb (necesitar� conexi�n a Internet si es la primera vez que lo ejecuta).
 
 3. Mientras tanto, puede comenzar a generar una llave adecuada para firmar gdb. Utilice [este enlace](action:keychain_access) para abrir el cuadro de configuraci�n de "Accesso a Llaves" de sus sistema y siga las siguientes instrucciones:
    1. In Keychain Access' list in the upper left hand corner of the window select "login".
    2. Go to the app menu (upper border of the screen) and select "Keychain Access" -> "Certificate Assistant" -> "Create a Certificate..."
    3. In the recently opened dialog, set the following settings: "Name"->"zinjai-gdb", "Identity Type"->"Self Signed Root", "Certificate Type"->"Code Signing"
    4. Click "Create", then "Continue", then "Done" to finish the wizard.
    5. Click on the "My Certificates" on one of the left side panels.
    6. In the main list of the window, double the new certificate: "zinjai-gdb" 
    7. Turn down the "Trust" disclosure triangle, scroll to the "Code sign" trust pulldown menu and select "Always Trust" and authenticate as needed using your username and password.
    8. Drag the new "zinjai-gdb" code signing from the "login" keychain to the "System" keychain in the Keychains pane on the left hand side of the main Keychain Access window. You'll have to authorize a few more times, and set it to be "Always trusted" when asked. ("sistema" "permitir siempre")
    9. Drag the new certificate from the Keychain Access window to the system Desktop.
    9. Go to the terminal launched in step one, wait for it to finish compiling and hit enter once when it asks you for the first time.
    10. In the keychain access dialog, drag "zinjai-gdb" back to "login". 
    10. Finally, you can close that window and hit enter one more time in the step one's terminal.
    
 4. Luego de finalizar con la compilaci�n de gdb del paso 2, y la generaci�n y aplicaci�n del nuevo certificado del paso 3, zinjai intentar� reiniciar el servicio que gestiona estos accesos. En caso de que este �ltimo paso falle, deber� reiniciar su sistema para que los cambios tengan efecto.

Si el proceso falla, igual puede utilizar ZinjaI para editar el c�digo, compilar, y ejecutar sus programas. Pero no podr� utilizar las funcionalidades del men� "Depuraci�n".


Instructions based on: [https://llvm.org/svn/llvm-project/lldb/trunk/docs/code-signing.txt](https://llvm.org/svn/llvm-project/lldb/trunk/docs/code-signing.txt)