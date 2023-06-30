#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

//Algunos de los requerimientos del supermercado son los siguientes:
//por cada botella de vino se tiene la siguiente informacion:
//1) código del vino
//2) nombre del Vino
//3) nombre de la marca
//4) año de fabricación: (dia,mes,año)
//5) fecha de ingreso al supermercado: (mes,año)
//6)tipo vino: malbec, tinto o blanco
//7) precio sin impuesto
//8) precio de venta al publico (+15%)
//9) datos del proveedor: (nombre,dni,telefono)

//1)
//Agregar productos al sistema. en caso de que no existan ya.
//2) Eliminar productos del sistema.
//3) Búsqueda por proveedor --- lista los productos despachados por ese proveedor.
//4) Búsqueda por vino -----lista la info de los vinos (nombre)
//5) Modificar precio del producto ---- permite modificar el precio de un producto (código)
//6) Modificar fecha de ingreso al supermercado de un determinado vino.
//7) Imprimir productos -- genera un archivo. txt con la información del producto (código)
//8) Imprimir teléfono de un proveedor ---- genera un archivo.txt con los datos de un proveedor.
//9) Total de productos --.
//-- genera un archivo. txt con la info de todos los vinos y al final
//muestra la suma total de todos sus precios de venta al publico


struct Vino{
    int codigo;
    std::string nombre;
    std::string marca;
    int anioFabricacion[3];
    int fechaIngreso[2];
    std::string tipoVino;
    float precioSinImpuesto;
    float precioVentaPublico;
    std::string nombreProveedor;
    int dniProveedor;
    int telefonoProveedor;
};


//Calcular el precio para la venta al publico del vino
float ventaPublico(float precioSinImpuesto) {
    float porcentajeImpuesto = 0.15;
    float precioVentaPublico = precioSinImpuesto * (1 + porcentajeImpuesto);
    return precioVentaPublico;
}

//Convertir a Mayusculas
std::string convertirAMayusculas(const std::string& texto) {
    std::string textoMayusculas = texto;
    std::transform(textoMayusculas.begin(), textoMayusculas.end(), textoMayusculas.begin(), ::toupper);
    return textoMayusculas;
}

//Validacion de las fechas
bool esFechaValida(int anio, int mes, int dia) {
    // Año 1981-2099
    if (anio < 1981 || anio > 2023  ) {
        return false;
    }
    // Mes 1-12
    if (mes < 1 || mes > 12 ) {
        return false;
    }
    // Dia 1-31
    if (dia < 1 || dia > 31 ) {
        return false;
    }
    // Mes de 30 días
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) {
        return false;
    }
    // Años bisiestos
    if (mes == 2) {
        bool esBisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
        if ((esBisiesto && dia > 29) || (!esBisiesto && dia > 28)) {
            return false;
        }
    }
    return true;
}

//De precios y datos del proveedor

bool validarPrecio(float precioSinImpuesto) {
    if (precioSinImpuesto < 0) {
        return false;
    }
    return true;
}

//Validacion de tipo de vino
bool validarTipoVino(const std::string tipoVino) {
    std::string tipoVinoFuncion = convertirAMayusculas(tipoVino);
    if (tipoVinoFuncion == "MALBEC" || tipoVinoFuncion == "TINTO" || tipoVinoFuncion == "BLANCO") {
        return true;
    }
    return false;
}

//Validacion fecha de creacion con fecha de ingreso

bool validarFechaIngreso(int anioFabricacion[3], int fechaIngreso[2]) {
    if (anioFabricacion[0] > fechaIngreso[0]) {
        return false;
    }
    if (anioFabricacion[0] == fechaIngreso[0] && anioFabricacion[1] > fechaIngreso[1]) {
        return false;
    }
    return true;
}

//Validacion de DNI
bool validarDNI(int dni) {
    if (dni < 1000000 || dni > 99999999) {
        return false;
    }
    return true;
}

//Validacion de telefono
bool validarTelefono(int telefono) {
    if (telefono < 1 || telefono > 999999999) {
        return false;
    }
    return true;
}

// Función para verificar si se ingresó un punto incorrectamente en las fechas
bool verificarPunto(int anio, int mes, int dia) {
    std::string fecha = std::to_string(anio) + "." + std::to_string(mes) + "." + std::to_string(dia);
    size_t puntoPos = fecha.find(".");
    return puntoPos != std::string::npos && puntoPos != fecha.size() - 1;
}


//Agregar Productos
void agregarProducto(std::vector<Vino>& vinos) {
    Vino nuevoVino;

    nuevoVino.codigo = vinos.size() + 1;

    std::cout << "\n--Datos del vino--\n" << std::endl;
    std::cout << "El codigo de este vino sera el siguiente: " << nuevoVino.codigo << std::endl;
    std::cout << "Ingrese el nombre del vino: "<< std::endl;
    std::cin >> nuevoVino.nombre;

    std::cout << "Ingrese la marca del vino: "<< std::endl;
    std::cin >> nuevoVino.marca;
    system("cls");

    std::cout << "\n--Fechas del Vino--\n" << std::endl;

    // Ingresar y verificación de Fechas
    do {
        do {
            std::cout << "Ingrese el anio de fabricacion del vino (formato: AAAA): ";
            std::cin >> nuevoVino.anioFabricacion[0];
            std::cout << "Ingrese el mes de fabricacion del vino (formato: MM): ";
            std::cin >> nuevoVino.anioFabricacion[1];
            std::cout << "Ingrese el dia de fabricacion del vino (formato: DD): ";
            std::cin >> nuevoVino.anioFabricacion[2];

            if (!esFechaValida(nuevoVino.anioFabricacion[0], nuevoVino.anioFabricacion[1], nuevoVino.anioFabricacion[2])) {
                std::cout << "Fecha de fabricacion invalida. Ingrese una fecha valida." << std::endl;
                std::cout << " " << std::endl;
            }
            else if (verificarPunto(nuevoVino.anioFabricacion[0], nuevoVino.anioFabricacion[1], nuevoVino.anioFabricacion[2])) {
                std::cout << "Fecha de fabricacion invalida. No debe haber un punto decimal en la fecha. Ingrese una fecha valida." << std::endl;
                std::cout << " " << std::endl;
            }
        } while (!esFechaValida(nuevoVino.anioFabricacion[0], nuevoVino.anioFabricacion[1], nuevoVino.anioFabricacion[2]) || verificarPunto(nuevoVino.anioFabricacion[0], nuevoVino.anioFabricacion[1], nuevoVino.anioFabricacion[2]));

        do {
            system("cls");
            std::cout << "Ingrese el anio de ingreso del vino (formato: AAAA): ";
            std::cin >> nuevoVino.fechaIngreso[0];
            std::cout << "Ingrese el mes de ingreso del vino (formato: MM): ";
            std::cin >> nuevoVino.fechaIngreso[1];

            if (!esFechaValida(nuevoVino.fechaIngreso[0], nuevoVino.fechaIngreso[1], 1)) {
                std::cout << "Fecha de ingreso invalida. Ingrese una fecha valida." << std::endl;
                std::cout << " " << std::endl;
            }
            else if (verificarPunto(nuevoVino.fechaIngreso[0], nuevoVino.fechaIngreso[1], 1)) {
                std::cout << "Fecha de ingreso invalida. No debe haber un punto decimal en la fecha. Ingrese una fecha valida." << std::endl;
                std::cout << " " << std::endl;
            }
        } while (!esFechaValida(nuevoVino.fechaIngreso[0], nuevoVino.fechaIngreso[1], 1) || verificarPunto(nuevoVino.fechaIngreso[0], nuevoVino.fechaIngreso[1], 1));

        if (!validarFechaIngreso(nuevoVino.anioFabricacion, nuevoVino.fechaIngreso)) {
            std::cout << "Fecha de ingreso invalida (Fecha de creacion o de ingreso al supermercado incorrecta). Ingrese una fecha valida." << std::endl;
            std::cout << " " << std::endl;
        }
        else {
            std::cout << "Fecha de ingreso valida" << std::endl;
            std::cout << " " << std::endl;
        }

    } while (!validarFechaIngreso(nuevoVino.anioFabricacion, nuevoVino.fechaIngreso));



    system("cls");

    do {
        std::cout << "\n--Informacion para Supermercado--\n" << std::endl;
        std::cout << "Ingrese el tipo de vino: "<< std::endl;
        std::cout << "Los tipos de vinos son, Malbec, Blanco, Tinto "<< std::endl;
        std::cin >> nuevoVino.tipoVino;
        if (validarTipoVino(nuevoVino.tipoVino)) {
            std::cout << "Tipo de vino Valido" << std::endl;
        }else {
            std::cout << "Tipo de vino invalido. Ingrese un tipo de vino valido."  << std::endl;
        }

    }while(!validarTipoVino(nuevoVino.tipoVino));

    do {
        std::cout << "Ingrese el precio sin impuesto del vino: "<< std::endl;
        std::cin >> nuevoVino.precioSinImpuesto;
        nuevoVino.precioVentaPublico = ventaPublico(nuevoVino.precioSinImpuesto);

        if(!validarPrecio(nuevoVino.precioSinImpuesto)){
            std::cout << "Precio ingresado correctamente." << std::endl;
        }else{
            std::cout << "Precio invalido. Ingrese un precio valido." << std::endl;
        }

    }while(!validarPrecio(nuevoVino.precioSinImpuesto));



    system("cls");

    std::cout << "\n--Datos Proveedor--\n" << std::endl;
    std::cout << "Ingrese el nombre del proveedor: "<< std::endl;
    std::cin >> nuevoVino.nombreProveedor;

    do {
        std::cout << "Ingrese el DNI del proveedor: "<< std::endl;
        std::cin >> nuevoVino.dniProveedor;

        if (!validarDNI(nuevoVino.dniProveedor)) {
            std::cout << "DNI invalido. Ingrese un DNI valido." << std::endl;
        }else {
            std::cout << "DNI valido" << std::endl;
        }
    }while(!validarDNI(nuevoVino.dniProveedor));

    do {
        std::cout << "Ingrese el telefono del proveedor: "<< std::endl;
        std::cin >> nuevoVino.telefonoProveedor;

        if (!validarTelefono(nuevoVino.telefonoProveedor)) {
            std::cout << "Telefono invalido. Ingrese un telefono valido." << std::endl;
        }else {
            std::cout << "Telefono valido" << std::endl;
        }
    }while(!validarTelefono(nuevoVino.telefonoProveedor));

    system("cls");

    vinos.push_back(nuevoVino);
    std::cout << "Producto agregado correctamente." << std::endl;
}

//Eliminar Productos
void eliminarProducto(std::vector<Vino>& vinos, int codigo) {
    for (auto i = vinos.begin(); i != vinos.end(); ++i) {
        if (i->codigo == codigo) {
            vinos.erase(i);
            std::cout << "Producto eliminado correctamente." << std::endl;
            return;
        }
    }

    std::cout << "No se encontro un producto con el codigo especificado." << std::endl;
}

//Busqueda de productos por proveedor
void mostrarProductoProveedor(std::vector<Vino>& vinos, int dni){
    for(auto i = vinos.begin(); i != vinos.end(); i++){
        if(i->dniProveedor == dni){
            std::cout << "------ Informacion del vino ------" << std::endl;
            std::cout << "Codigo: " << i->codigo << std::endl;
            std::cout << "Nombre: " << i->nombre << std::endl;
            std::cout << "Marca: " << i->marca << std::endl;
            std::cout << "Anio de fabricacion: " << i->anioFabricacion[0] << "/" << i->anioFabricacion[1] << "/" << i->anioFabricacion[2] << std::endl;
            std::cout << "Fecha de ingreso: " << i->fechaIngreso[0] << "/" << i->fechaIngreso[1] << std::endl;
            std::cout << "Tipo de vino: " << i->tipoVino << std::endl;
            std::cout << "Precio sin impuesto: " << i->precioSinImpuesto << std::endl;
            std::cout << "Precio de venta al publico: " << i->precioVentaPublico << std::endl;
            std::cout << "Nombre del proveedor: " << i->nombreProveedor << std::endl;
            std::cout << "DNI del proveedor: " << i->dniProveedor << std::endl;
            std::cout << "Telefono del proveedor: " << i->telefonoProveedor << std::endl;
            return;
        }
    }
}

//Busqueda de productos segun el nombre del vino
void mostrarProducto(std::vector<Vino>& vinos, std::string nombreVino){
    for (auto i = vinos.begin(); i != vinos.end(); ++i) {
        if (i->nombre == nombreVino) {
            std::cout << "------ Informacion del vino ------" << std::endl;
            std::cout << "Codigo: " << i->codigo << std::endl;
            std::cout << "Nombre: " << i->nombre << std::endl;
            std::cout << "Marca: " << i->marca << std::endl;
            std::cout << "Anio de fabricacion: " << i->anioFabricacion[0] << "/" << i->anioFabricacion[1] << "/" << i->anioFabricacion[2] << std::endl;
            std::cout << "Fecha de ingreso: " << i->fechaIngreso[0] << "/" << i->fechaIngreso[1] << std::endl;
            std::cout << "Tipo de vino: " << i->tipoVino << std::endl;
            std::cout << "Precio sin impuesto: " << i->precioSinImpuesto << std::endl;
            std::cout << "Precio de venta al publico: " << i->precioVentaPublico << std::endl;
            std::cout << "Nombre del proveedor: " << i->nombreProveedor << std::endl;
            std::cout << "DNI del proveedor: " << i->dniProveedor << std::endl;
            std::cout << "Telefono del proveedor: " << i->telefonoProveedor << std::endl;
            return;
        }
    }

    std::cout << "No se encontro un producto con el nombre especificado." << std::endl;
}

//Modificar precio del producto, busqueda por codigo del vino

void modifPrecio(std::vector<Vino>& vinos, int codigo){
    for (auto i = vinos.begin(); i != vinos.end(); ++i) {
        if (i->codigo == codigo) {
            std::cout << "Ingrese el nuevo precio sin impuesto del vino: "<< std::endl;
            std::cin >> i->precioSinImpuesto;
            if(i->precioSinImpuesto < 0){
                std::cout << "El precio no puede ser negativo." << std::endl;
                return;
            }else{
                i->precioVentaPublico = ventaPublico(i->precioSinImpuesto);
                std::cout << "Precio modificado correctamente." << std::endl;
                return;
            }
        }
    }

    std::cout << "No se encontro un producto con el codigo especificado." << std::endl;
}

//Modificar fecha de ingreso al supermercado de un determinado vino


void modificarIngresoVino(std::vector<Vino>& vinos, const std::string& nombreVino) {
    for (auto i = vinos.begin(); i != vinos.end(); ++i) {
        if (i->nombre == nombreVino) {
            bool fechaValida = false;
            do {
                system("cls");
                std::cout << "Fecha de creacion del vino: " << i->fechaIngreso[0] << "-" << i->fechaIngreso[1] << std::endl;
                std::cout << "Fecha de ingreso actual: " << i->fechaIngreso[0] << "-" << i->fechaIngreso[1] << std::endl;
                std::cout << "Ingrese el nuevo anio de ingreso del vino (formato: AAAA): ";
                std::cin >> i->fechaIngreso[0];
                std::cout << "Ingrese el nuevo mes de ingreso del vino (formato: MM): ";
                std::cin >> i->fechaIngreso[1];

                if (!esFechaValida(i->fechaIngreso[0], i->fechaIngreso[1], 1) || !validarFechaIngreso(i->anioFabricacion, i->fechaIngreso)) {
                    std::cout << "Fecha de ingreso invalida. Ingrese una fecha valida." << std::endl;
                    std::cout << std::endl;
                } else {
                    fechaValida = true;
                }
            } while (!fechaValida);

            std::cout << "Fecha de ingreso modificada correctamente." << std::endl;
            return;
        }
    }

    std::cout << "No se encontró un producto con el nombre especificado." << std::endl;
}


//Imprimir un solo producto
void imprimirProductoPorNombre(const std::vector<Vino>& vinos, const std::string& nombreVino) {
    bool productoEncontrado = false;

    for (const auto& vino : vinos) {
        if (vino.nombre == nombreVino) {
            std::ostringstream nombreArchivo;
            nombreArchivo << "../archivos/" << vino.nombre << ".txt";

            std::ofstream archivo(nombreArchivo.str());

            archivo << "------ Informacion del vino ------" << std::endl;
            archivo << "Codigo: " << vino.codigo << std::endl;
            archivo << "Nombre: " << vino.nombre << std::endl;
            archivo << "Marca: " << vino.marca << std::endl;
            archivo << "Anio de fabricacion: " << vino.anioFabricacion[0] << "/"
                    << vino.anioFabricacion[1] << "/" << vino.anioFabricacion[2] << std::endl;
            archivo << "Fecha de ingreso: " << vino.fechaIngreso[0] << "/"
                    << vino.fechaIngreso[1] << std::endl;
            archivo << "Tipo de vino: " << vino.tipoVino << std::endl;
            archivo << "Precio sin impuesto: " << vino.precioSinImpuesto << std::endl;
            archivo << "Precio de venta al publico: " << vino.precioVentaPublico << std::endl;
            archivo << "Nombre del proveedor: " << vino.nombreProveedor << std::endl;
            archivo<< "DNI del proveedor: " << vino.dniProveedor << std::endl;
            archivo << "Telefono del proveedor: " << vino.telefonoProveedor << std::endl;
            archivo << "---------------------------------" << std::endl;

            archivo.close();

            productoEncontrado = true;
            break;
        }
    }

    if (!productoEncontrado) {
        std::cout << "No se encontró un producto con el nombre especificado." << std::endl;
    }
}

// Función para imprimir los datos de un proveedor y guardarlos en un archivo
void imprimirProveedor(const std::vector<Vino>& proveedores, const std::string& nombreProveedor) {
    bool proveedorEncontrado = false;

    for (const auto& vino : proveedores) {
        if (vino.nombreProveedor == nombreProveedor) {
            std::ostringstream nombreArchivo;
            nombreArchivo << "../archivos/" << vino.nombreProveedor << ".txt";

            std::ofstream archivo(nombreArchivo.str());

            archivo << "------ Informacion del proveedor ------" << std::endl;
            archivo << "Nombre: " << vino.telefonoProveedor << std::endl;
            archivo << "Telefono: " << vino.telefonoProveedor << std::endl;
            archivo << "Direccion: " << vino.dniProveedor << std::endl;
            archivo << "--------------------------------------" << std::endl;

            archivo.close();

            proveedorEncontrado = true;
            break;
        }
    }

    if (!proveedorEncontrado) {
        std::cout << "No se encontro un proveedor con el nombre especificado." << std::endl;
    }
}

// Función para imprimir los datos de los productos y de los proveedores y guardarlos en un archivo
void imprimirTodo(const std::vector<Vino>& vinos) {
    std::ostringstream nombreArchivo;
    nombreArchivo << "../archivos/" << "productos.txt";

    std::ofstream archivo(nombreArchivo.str());

    archivo << "------ Informacion de los productos ------" << std::endl;

    for (const auto& vino : vinos) {
        archivo << "Codigo: " << vino.codigo << std::endl;
        archivo << "Nombre: " << vino.nombre << std::endl;
        archivo << "Marca: " << vino.marca << std::endl;
        archivo << "Anio de fabricacion: " << vino.anioFabricacion[0] << "/"
                << vino.anioFabricacion[1] << "/" << vino.anioFabricacion[2] << std::endl;
        archivo << "Fecha de ingreso: " << vino.fechaIngreso[0] << "/"
                << vino.fechaIngreso[1] << std::endl;
        archivo << "Tipo de vino: " << vino.tipoVino << std::endl;
        archivo << "Precio sin impuesto: " << vino.precioSinImpuesto << std::endl;
        archivo << "Precio de venta al publico: " << vino.precioVentaPublico << std::endl;
        archivo << "Nombre del proveedor: " << vino.nombreProveedor << std::endl;
        archivo<< "DNI del proveedor: " << vino.dniProveedor << std::endl;
        archivo << "Telefono del proveedor: " << vino.telefonoProveedor << std::endl;
        archivo << "---------------------------------" << std::endl;
    }

    archivo.close();
}

int main() {
    //Variables de uso para distintas busquedas en el sistema
    std::vector <Vino> vinos;
    int opcion1;
    std::string opcion2;
    int codigo;
    int dni;
    std::string nombreVino;
    std::string nombreProveedor;

    do {
        std::cout << "------ Menu ------" << std::endl;
        std::cout << "1) Agregar productos al sistema." << std::endl;
        std::cout << "2) Eliminar productos del sistema." << std::endl;
        std::cout << "3) Busqueda por proveedor." << std::endl;
        std::cout << "4) Busqueda por vino." << std::endl;
        std::cout << "5) Modificar precio del producto." << std::endl;
        std::cout << "6) Modificar fecha de ingreso al supermercado de un determinado vino." << std::endl;
        std::cout << "7) Imprimir productos." << std::endl;
        std::cout << "8) Imprimir telefono de un proveedor." << std::endl;
        std::cout << "9) Total de productos." << std::endl;
        std::cout << "0) Salir." << std::endl;
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion1;
        system("cls");

        switch (opcion1) {
            case 1://AGREGAR PRODUCTO
                system("cls");
                agregarProducto(vinos);
                system("cls");
                break;
            case 2://ELIMINAR PRODUCTO
                system("cls");
                std::cout << "\n--Eliminar Producto--\n";
                std::cout << "Ingrese el codigo del producto a eliminar: ";
                std::cin >> codigo;
                eliminarProducto(vinos, codigo);
                system("cls");
                break;
            case 3://BUSQUEDA POR PROVEEDOR
                std::cout << "Ingrese el dni del proovedor: ";
                std::cin >> dni;
                mostrarProductoProveedor(vinos, dni);
                system("pause");
                system("cls");
                break;
            case 4://BUSQUEDA POR VINO
                system("cls");
                std::cout << "\n--Busqueda de producto(Nombre Vino)--\n";
                std::cout << "Ingrese el nombre del vino\n";
                std::cin >> nombreVino;
                system("cls");
                mostrarProducto(vinos, nombreVino);
                system("pause");
                system("cls");
                break;
            case 5://MODIFICAR PRECIO DEL PRODUCTO
                system("cls");
                std::cout << "\n--Modificar precio del producto--\n";
                std::cout << "Ingrese el codigo del producto a modificar: ";
                std::cin >> codigo;
                modifPrecio(vinos, codigo);
                system("cls");
                break;
            case 6://MODIFICAR FECHA DE INGRESO AL SUPERMERCADO DE UN DETERMINADO VINO
                system("cls");
                std::cout << "\n--Modificar fecha de ingreso al supermercado de un determinado vino--\n";
                std::cout << "Ingrese el nombre del vino: ";
                std::cin >> nombreVino;
                modificarIngresoVino(vinos, nombreVino);
                system("cls");
                break;
            case 7://IMPRIMIR PRODUCTOS
                system("cls");
                std::cout << "\n--Imprimir un producto--\n";
                std::cout << "Ingrese el nombre del vino a imprimir: ";
                std::cin >> nombreVino;
                imprimirProductoPorNombre(vinos, nombreVino);
                std::cout << "Se ha guardado la informacion en el archivo " << nombreVino << ".txt" << std::endl;
                system("pause");
                system("cls");
                break;
            case 8://IMPRIMIR TELEFONO DE UN PROVEEDOR
                system("cls");
                std::cout << "Ingrese el nombre del proveedor: ";
                std::cin >> nombreProveedor;
                imprimirProveedor(vinos, nombreProveedor);
                std::cout << "Se ha guardado la informacion en el archivo " << nombreProveedor << ".txt" << std::endl;
                system("pause");
                system("cls");
                break;
            case 9://TOTAL DE PRODUCTOS
                system("cls");
                std::cout << "El total de productos es: " << vinos.size() << std::endl;
                imprimirTodo(vinos);
                std::cout << "Se ha guardado la informacion en el archivo productos.txt" << std::endl;
                system("pause");
                system("cls");
                break;
            case 0:
                std::cout << "¿Esta seguro que desea salir? (s/n): ";
                std::cin >> opcion2;
                if (opcion2 == "s") {
                    return 0;
                }
                break;
            default:
                std::cout << "Opcion invalida." << std::endl;
                break;
        }
    } while (opcion1 != 0);


    return 0;
}