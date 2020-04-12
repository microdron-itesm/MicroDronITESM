# MicroDronITESM Hi
Proyecto para colaboracion con el proyecto de Micro Dron
1. Clonar en una máquina con Linux, de preferencia Ubuntu 18, el proyecto MicroDronITESM. Desde línea de comandos, se debe de navegar a la carpeta donde se guardará y teclear:
`git clone --recurse-submodules https://github.com/microdron-itesm/MicroDronITESM.git >`
2. Se debe de tener el MPLAB IDE instalado en la máquina. Para hacerlo, se debe de acceder a la página del desarrollador Microchip y descargar la versión de Linux. Seguir las instrucciones de tal página para instalar.
3. Ya con MPLAB IDE, abrir el proyecto del MicroDron.X, encontrado dentro del directorio ./MicroDron/firmware
4. Para compilar el proyecto, es necesario utilizar el compilador XC32. Este se debe de descargar del sitio de desarrollador de Microchip. Para instalarlo, se debe de navegar en línea de comandos a tal carpeta y teclear:
`chmod u+x xc32-vX.XX-linux-installer.run`
`./xc32-vX.XX-linux-installer.run `
5. Tras haberlo instalado, debemos de agregar el compilador en MPLAB IDE. Para hacerlo, vamos a Tools > Options > Embedded > Build Tools > Add. Buscamos el archivo del compilador XC32 y lo seleccionamos.
6. Posteriormente, se debe de instalar Harmony v2.06. Este se puede descargar del sitio del desarrollador Microchip. Desde línea de comandos, repetimos el paso 4 para el archivo descargado de Harmony.
7. Al terminar la instalación, se debe de localizar el folder donde se instaló, y copiar los contenidos a una carpeta llamada Harmony en la raíz del repositorio de MicroDronITESM.
8. Casi para terminar, se debe agregar Harmony al proyecto MPLAB IDE y generar el código para el mismo. Para hacerlo, nos vamos a Tools > Plugins > Downloaded > Add Plugin. Ahí, encontramos la carpeta de instalación de Harmony y la agregamos al proyecto. 
9. Para generar el código, reiniciamos MPLAB IDE y vamos a Tools > Embedded > MPLAB Harmony Configurator. En la ventana abierta, hacemos click en el ícono con la palabra CODE y engranes.
10. En caso de que aparezca un error de no encontrar Harmony, decirle al programa que busque en la carpeta Harmony de la raíz del repositorio.
11. Ya está listo el proyecto para correr y programar el MicroDron.
