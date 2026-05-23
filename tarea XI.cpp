#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Producto {
    int codigo;
    char nombre[50];
    float precio;
    int stock;
    bool activo;
};

const char* ARCHIVO = "productos.dat"; 

void registrarProducto() {
    Producto p;
    ofstream archivo(ARCHIVO, ios::binary | ios::app);
    if (!archivo) {
        cout << "Error al abrir archivo.\n";
        return;
    }
    cout << "\n=== REGISTRAR PRODUCTO ===\n";
    cout << "Codigo: "; cin >> p.codigo;
    cin.ignore();
    cout << "Nombre: "; cin.getline(p.nombre, 50);
    cout << "Precio: "; cin >> p.precio;
    cout << "Stock: "; cin >> p.stock;
    p.activo = true;
    
    archivo.write((char*)&p, sizeof(Producto));
    archivo.close();
    cout << "Producto registrado correctamente.\n";
}

void listarProductos() {
    Producto p;
    ifstream archivo(ARCHIVO, ios::binary);
    if (!archivo) {
        cout << "No existe el archivo.\n";
        return;
    }
    cout << "\n=== LISTA DE PRODUCTOS ===\n";
    while (archivo.read((char*)&p, sizeof(Producto))) {
        if (p.activo) {
            cout << "Codigo: " << p.codigo << endl;
            cout << "Nombre: " << p.nombre << endl;
            cout << "Precio: Q " << p.precio << endl;
            cout << "Stock: " << p.stock << endl;
            cout << "-------------------------\n";
        }
    }
    archivo.close();
}

void buscarPorCodigo() {
    Producto p;
    int codigo;
    bool encontrado = false;
    ifstream archivo(ARCHIVO, ios::binary);
    
    if (!archivo) {
        cout << "No existe el archivo para buscar.\n";
        return;
    }

    cout << "\nIngrese codigo a buscar: ";
    cin >> codigo;
    
    while (archivo.read((char*)&p, sizeof(Producto))) {
        if (p.codigo == codigo && p.activo) {
            cout << "\nProducto encontrado:\n";
            cout << "Nombre: " << p.nombre << endl;
            cout << "Precio: Q " << p.precio << endl;
            cout << "Stock: " << p.stock << endl;
            encontrado = true;
            break;
        }
    }
    
    archivo.close();
    
    if (!encontrado) {
        cout << "\nProducto no encontrado o inactivo.\n";
    }
}

int main() {
    // Menú interactivo básico
    int opcion;
    do {
        cout << "\n=== MENÚ ===\n";
        cout << "1. Registrar producto\n";
        cout << "2. Listar productos\n";
        cout << "3. Buscar por codigo\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1: registrarProducto(); break;
            case 2: listarProductos(); break;
            case 3: buscarPorCodigo(); break;
            case 4: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);
    
    return 0;
}
