# Guía para comenzar con GitHub y subir tu primer programa en C/C++

## 1. Crear una cuenta en GitHub

GitHub es una plataforma para alojar y colaborar en proyectos de desarrollo de software. Para crear una cuenta:

1. Ve al sitio oficial: [https://github.com](https://github.com)
2. Haz clic en el botón **Sign up** (Registrarse) en la parte superior derecha.
3. Completa los campos requeridos:
   - Nombre de usuario
   - Dirección de correo electrónico
   - Contraseña
4. Verifica tu correo electrónico.
5. Opcionalmente, selecciona tus preferencias de configuración inicial.

> 💡 **Consejo útil:** Usa un nombre de usuario profesional, ya que será parte de la URL de tus repositorios (ej. `https://github.com/tu_usuario`).

---

## 2. Crear un repositorio con un programa "Hola Mundo" en C/C++

### Paso 1: Crear el repositorio

1. Inicia sesión en tu cuenta de GitHub.
2. Haz clic en el símbolo **+** en la esquina superior derecha y selecciona **New repository**.
3. Completa la información:
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
