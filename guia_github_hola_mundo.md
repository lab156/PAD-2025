# Guía para comenzar con GitHub y subir tu primer programa en C/C++

## 1. Crear una cuenta en GitHub

GitHub es una plataforma para alojar y colaborar en proyectos de desarrollo de software. Para crear una cuenta:

1. Visite al sitio oficial: [https://github.com](https://github.com)
2. Haga clic en el botón **Sign up** (Registrarse) en la parte superior derecha.
3. Complete los campos requeridos:
   - Nombre de usuario
   - Dirección de correo electrónico
   - Contraseña
4. Verifique tu correo electrónico.

>  💻 **Consejo útil:** Use un nombre de usuario profesional, ya que será parte de la URL de tus repositorios (ej. `https://github.com/tu_usuario`).

---

## 2. Crear un repositorio con un programa "Hola Mundo" en C/C++

### Paso 1: Crear el repositorio

1. Inicie sesión en tu cuenta de GitHub.
2. Haga clic en el símbolo **+** en la esquina superior derecha y selecciona **New repository**.
3. Complete la información:
   - **Repository name:** puede ser `hola-mundo-cpp`
   - **Description:** algo como "Mi primer programa en C/C++ en GitHub"
   - Selecciona si quieres que sea público o privado.
   - (Opcional) Marca "Add a README file"
4. Haz clic en **Create repository**.

---

### Paso 2: Crear el archivo `hola.cpp`

1. En el nuevo repositorio, haz clic en **Add file > Create new file**.
2. Escribe el nombre del archivo: `hola.cpp`
3. Copia y pega el siguiente código de ejemplo:

```cpp
#include <iostream>

int main() {
    std::cout << "Hola, mundo!" << std::endl;
    return 0;
}
```

4. Desplázate hacia abajo, agrega un mensaje de confirmación como "Agregar programa Hola Mundo".
5. Haz clic en **Commit new file**.

> ✅ **Listo!** Ahora tienes tu primer programa en C++ alojado en GitHub.

---

## Consejos adicionales

- 💻 Si tienes Git instalado en tu computadora, puedes clonar tu repositorio con:
  ```bash
  git clone https://github.com/tu_usuario/hola-mundo-cpp.git
  ```
- 🛠️ Para compilar el archivo localmente (si usas `g++`):
  ```bash
  g++ hola.cpp -o hola
  ./hola
  ```

---

## Recursos útiles

- [Documentación oficial de GitHub](https://docs.github.com/)
- [Instalar Git](https://git-scm.com/book/es/v2/Empezando-Instalación-de-Git)
- [Compilar programas C/C++ con g++](https://www.geeksforgeeks.org/compiling-a-c-program-using-g/)

---

## Opcional: Instalar WSL en una PC

Debido a que en esta clase es necesario escribir mucho código, necesita tener una plataforma (IDE) confiable de desarrollo. Pueden usar la plataforma con la que se sientan más cómodos. Una sugerencia es usar WSL.

WSL (Windows Subsystem for Linux) es una característica de Windows que permite ejecutar un entorno Linux directamente en Windows, sin necesidad de una máquina virtual o arranque dual. Esto significa que puedes utilizar herramientas y aplicaciones de Linux en Windows, junto con tus herramientas y aplicaciones de Windows existentes. 
[https://learn.microsoft.com/es-es/windows/wsl/about](microsoft.com)

### Instalación
La instalacion de WSL es algo distinta de  instalar cualquier otro programa en Windows. Algunas guías utiles son:
* https://learn.microsoft.com/en-us/windows/wsl/install
* https://ubuntu.com/desktop/wsl

# Cómo Instalar WSL (Subsistema de Windows para Linux)

Esta guía te mostrará cómo instalar el Subsistema de Windows para Linux (WSL) en tu máquina con Windows. WSL te permite ejecutar un entorno GNU/Linux directamente en Windows, sin la necesidad de una máquina virtual tradicional o un arranque dual.

---

## Requisitos Previos

Antes de comenzar, asegúrate de que tu sistema cumpla con los siguientes requisitos:

* **Windows 10 versión 2004 y superior** (Build 19041 y superior) o **Windows 11**.
    * Para verificar tu versión, presiona la tecla `Windows` + `R`, escribe `winver` y presiona Enter.
* La **virtualización** debe estar habilitada en la BIOS/UEFI de tu computadora.
    * Puedes verificar esto en el Administrador de Tareas ( pestaña "Rendimiento", sección "CPU"). Si dice "Virtualización: Deshabilitada", deberás habilitarla en la configuración de la BIOS/UEFI de tu sistema al reiniciar. El método para acceder a la BIOS/UEFI varía según el fabricante (comúnmente usando teclas como `Supr`, `F2`, `F10`, `F12` o `Esc` durante el arranque).

---

## Instalación Simplificada (Recomendado)

La forma más sencilla de instalar WSL es usando un solo comando en PowerShell o el Símbolo del sistema.

1.  **Abrir PowerShell como Administrador:**
    * Busca "PowerShell" en el menú de inicio.
    * Haz clic derecho sobre "Windows PowerShell".
    * Selecciona "Ejecutar como administrador".

2.  **Ejecutar el comando de instalación:**
    * En la ventana de PowerShell (Administrador), escribe el siguiente comando y presiona Enter:
        ```powershell
        wsl --install
        ```
    * Este comando realizará automáticamente lo siguiente:
        * Habilitará las características opcionales necesarias para WSL.
        * Descargará la versión más reciente del kernel de Linux.
        * Establecerá WSL 2 como la versión predeterminada.
        * Instalará la distribución de Linux **Ubuntu** por defecto.

3.  **Reiniciar tu computadora:**
    * Una vez que el comando haya finalizado, reinicia tu computadora para completar la instalación.

4.  **Configurar tu distribución de Linux:**
    * Después de reiniciar, busca "Ubuntu" (o la distribución que se haya instalado) en el menú de inicio y ábrela.
    * La primera vez que la ejecutes, se te pedirá que esperes unos minutos mientras se configuran los archivos.
    * Luego, se te pedirá que crees un **nombre de usuario** y una **contraseña** para tu entorno Linux. Estas credenciales son específicas para Linux y no tienen que coincidir con tus credenciales de Windows. ¡Asegúrate de recordarlas!

---

> **Recomendación**: Para la clase, instale una distribucion común como Ubuntu.

---

## Instalación de Otras Distribuciones de Linux (Opcional)

Si deseas instalar una distribución de Linux diferente a Ubuntu, o instalar distribuciones adicionales:

1.  **Listar distribuciones disponibles:**
    * Abre PowerShell como Administrador y ejecuta:
        ```powershell
        wsl --list --online
        ```
    * Esto mostrará una lista de las distribuciones de Linux disponibles para instalar.

2.  **Instalar una distribución específica:**
    * Usa el siguiente comando, reemplazando `<NombreDeLaDistro>` con el nombre de la distribución que deseas instalar (por ejemplo, `Debian`, `openSUSE-Leap-15.5`, etc.):
        ```powershell
        wsl --install -d <NombreDeLaDistro>
        ```

---

## Comandos Útiles de WSL

Una vez instalado, puedes gestionar WSL desde PowerShell o el Símbolo del sistema:

* **Listar distribuciones instaladas:**
    ```powershell
    wsl --list --verbose
    ```
    Esto te mostrará las distribuciones que tienes instaladas, su estado y la versión de WSL que están utilizando.

* **Establecer una distribución predeterminada:**
    ```powershell
    wsl --set-default <NombreDeLaDistro>
    ```

* **Establecer la versión de WSL para una distribución (1 o 2):**
    ```powershell
    wsl --set-version <NombreDeLaDistro> <NumeroDeVersion>
    ```
    (Por ejemplo, `wsl --set-version Ubuntu-22.04 2`)

* **Acceder a tu distribución de Linux:**
    * Simplemente escribe el nombre de tu distribución (ej. `ubuntu`) en el Símbolo del sistema o PowerShell y presiona Enter.
    * Alternativamente, busca la aplicación de la distribución en el menú de inicio.

¡Felicidades! Ahora tienes WSL instalado y listo para usar. 🎉




