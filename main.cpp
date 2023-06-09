#include <iostream>
#include <string>
#include <vector>



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
//9) datos del proveedor: (nombre, telefono/

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
//muestra la suma total de todos sus precios de venta al publico.


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

void agregarProducto(std::vector<Vino>& vinos) {
    Vino nuevoVino;

    nuevoVino.codigo = vinos.size() + 1;

    std::cout << "\n--Datos del vino--\n" << std::endl;
    std::cout << "Ingrese el nombre del vino: "<< std::endl;
    std::cin >> nuevoVino.nombre;

    std::cout << "Ingrese la marca del vino: "<< std::endl;
    std::cin >> nuevoVino.marca;
    system("cls");

    std::cout << "\n--Fechas del Vino--\n" << std::endl;
    std::cout << "Ingrese el anio de fabricación del vino (formato: AAAA): "<< std::endl;
    std::cin >> nuevoVino.anioFabricacion[0];
    std::cout << "Ingrese el mes de fabricación del vino (formato: MM): "<< std::endl;
    std::cin >> nuevoVino.anioFabricacion[1];
    std::cout << "Ingrese el día de fabricación del vino (formato: DD): "<< std::endl;
    std::cin >> nuevoVino.anioFabricacion[2];

    std::cout << "Ingrese el anio de ingreso del vino (formato: AAAA): "<< std::endl;
    std::cin >> nuevoVino.fechaIngreso[0];
    std::cout << "Ingrese el mes de ingreso del vino (formato: MM): "<< std::endl;
    std::cin >> nuevoVino.fechaIngreso[1];
    system("cls");

    std::cout << "\n--Informacion para Supermercado--\n" << std::endl;
    std::cout << "Ingrese el tipo de vino: "<< std::endl;
    std::getline(std::cin, nuevoVino.tipoVino);

    std::cout << "Ingrese el precio sin impuesto del vino: "<< std::endl;
    std::cin >> nuevoVino.precioSinImpuesto;

    nuevoVino.precioVentaPublico = ventaPublico(nuevoVino.precioSinImpuesto);
    system("cls");

    std::cout << "\n--Datos Proveedor--\n" << std::endl;
    std::cout << "Ingrese el nombre del proveedor: "<< std::endl;
    std::cin >> nuevoVino.nombreProveedor;

    std::cout << "Ingrese el DNI del proveedor: "<< std::endl;
    std::cin >> nuevoVino.dniProveedor;

    std::cout << "Ingrese el teléfono del proveedor: "<< std::endl;
    std::cin >> nuevoVino.telefonoProveedor;
    system("cls");

    vinos.push_back(nuevoVino);
    std::cout << "Producto agregado correctamente." << std::endl;
}

void eliminarProducto(std::vector<Vino>& vinos, int codigo) {
    for (auto i = vinos.begin(); i != vinos.end(); ++i) {
        if (i->codigo == codigo) {
            vinos.erase(i);
            std::cout << "Producto eliminado correctamente." << std::endl;
            return;
        }
    }

    std::cout << "No se encontró un producto con el código especificado." << std::endl;
}

void mostrarProductoProveedor(std::vector<Vino>& vinos, int dni){
    for(auto i = vinos.begin(); i != vinos.end(); i++){
        if(i->dniProveedor == dni){
            std::cout << "------ Informacion del vino ------" << std::endl;
            std::cout << "Código: " << i->codigo << std::endl;
            std::cout << "Nombre: " << i->nombre << std::endl;
            std::cout << "Marca: " << i->marca << std::endl;
            std::cout << "Año de fabricación: " << i->anioFabricacion[0] << "/" << i->anioFabricacion[1] << "/" << i->anioFabricacion[2] << std::endl;
            std::cout << "Fecha de ingreso: " << i->fechaIngreso[0] << "/" << i->fechaIngreso[1] << std::endl;
            std::cout << "Tipo de vino: " << i->tipoVino << std::endl;
            std::cout << "Precio sin impuesto: " << i->precioSinImpuesto << std::endl;
            std::cout << "Precio de venta al publico: " << i->precioVentaPublico << std::endl;
            std::cout << "Nombre del proveedor: " << i->nombreProveedor << std::endl;
            std::cout << "Telefono del proveedor: " << i->telefonoProveedor << std::endl;
            return;
        }
    }
}

void mostrarProducto(std::vector<Vino>& vinos, std::string nombreVino){
    for (auto i = vinos.begin(); i != vinos.end(); ++i) {
        if (i->nombre == nombreVino) {
            std::cout << "------ Informacion del vino ------" << std::endl;
            std::cout << "Código: " << i->codigo << std::endl;
            std::cout << "Nombre: " << i->nombre << std::endl;
            std::cout << "Marca: " << i->marca << std::endl;
            std::cout << "Año de fabricación: " << i->anioFabricacion[0] << "/" << i->anioFabricacion[1] << "/" << i->anioFabricacion[2] << std::endl;
            std::cout << "Fecha de ingreso: " << i->fechaIngreso[0] << "/" << i->fechaIngreso[1] << std::endl;
            std::cout << "Tipo de vino: " << i->tipoVino << std::endl;
            std::cout << "Precio sin impuesto: " << i->precioSinImpuesto << std::endl;
            std::cout << "Precio de venta al público: " << i->precioVentaPublico << std::endl;
            std::cout << "Nombre del proveedor: " << i->nombreProveedor << std::endl;
            std::cout << "Teléfono del proveedor: " << i->telefonoProveedor << std::endl;
            return;
        }
    }

    std::cout << "No se encontró un producto con el nombre especificado." << std::endl;
}


int main() {
    std::vector <Vino> vinos;
    int opcion1;
    std::string opcion2;
    int codigo;
    int dni;
    std::string nombreVino;

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
                break;
            case 4://BUSQUEDA POR VINO
                system("cls");
                std::cout << "\n--Busqueda de producto(Nombre Vino)--\n";
                std::cout << "Ingrese el nombre del vino\n";
                std::cin >> nombreVino;
                mostrarProducto(vinos, nombreVino);
                break;
            case 5://MODIFICAR PRECIO DEL PRODUCTO
                break;
            case 6://MODIFICAR FECHA DE INGRESO AL SUPERMERCADO DE UN DETERMINADO VINO
                break;
            case 7://IMPRIMIR PRODUCTOS
                break;
            case 8://IMPRIMIR TELEFONO DE UN PROVEEDOR
                break;
            case 9://TOTAL DE PRODUCTOS
                break;
            case 0:
                std::cout << "¿Está seguro que desea salir? (s/n): ";
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