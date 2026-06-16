#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip> 

using namespace std;


struct Producto {
    int codigo;
    string nombre;
    double precioColones;
};


struct Cliente {
    string placa;
    string nombre;
    string cedula;
    string estado; 
    string telefono;
    string fechaEntrada;
    string detalle;
    string repuestosAsignados; 
    double totalPagar;
};


void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


void mostrarMenu() {
    cout << "\n==================================================\n";
    cout << "                    GRUPO 6                       \n";
    cout << "==================================================\n";
    cout << "1. Registro de clientes\n";
    cout << "2. Actualizacion del estado de clientes\n";
    cout << "3. Inventarios de repuestos (Agregar producto a cliente)\n";
    cout << "4. Ver catalogo de productos y precios (Colones)\n";
    cout << "5. Ver todos los clientes registrados\n";
    cout << "6. Salir del sistema\n";
    cout << "==================================================\n";
    cout << "Seleccione una opcion: ";
}

int main() {

    vector<Producto> catalogo = {
        
        {101, "Aceite para Motor 20W50 (Litro)", 6500.0},
        {102, "Filtro de Aceite", 4500.0},
        {103, "Filtro de Aire", 8500.0},
        {104, "Pastillas de Freno (Set)", 18000.0},
        {105, "Liquido de Frenos", 3500.0},
        {106, "Bateria 12V", 45000.0},
        {107, "Coolant / Refrigerante (Galon)", 7500.0},

        // --- REPUESTOS ESPECÍFICOS DE MOTOR ---
        {201, "Kit de Pistones (Juego completo)", 85000.0},
        {202, "Anillos de Motor (Set)", 32000.0},
        {203, "Empaque de Cabeza / Culata", 22000.0},
        {204, "Bomba de Agua de Motor", 28500.0},
        {205, "Bomba de Aceite de Motor", 35000.0},
        {206, "Faja de Distribucion (Timing Belt)", 24000.0},
        {207, "Valvula de Admision (Unidad)", 6000.0},
        {208, "Valvula de Escape (Unidad)", 6500.0},
        {209, "Sensor de Oxigeno", 29000.0},
        {210, "Soportes de Motor (Juego)", 42000.0}
    };

    vector<Cliente> listaClientes;
    int opcion = 0;


    while (true) {
        mostrarMenu();
        cin >> opcion;

     
        if (cin.fail()) {
            cout << "\n[ERROR] Entrada invalida. Por favor, ingrese un numero del 1 al 6.\n";
            limpiarEntrada();
            continue;
        }

        limpiarEntrada();

        if (opcion == 6) {
            cout << "Saliendo del sistema. ¡Hasta luego!\n";
            break;
        }

        switch (opcion) {
        case 1: {
           
            Cliente nuevo;
            cout << "\n--- REGISTRO DE NUEVO CLIENTE ---\n";

            cout << "Placa: ";
            getline(cin, nuevo.placa);

            cout << "Cliente (Nombre): ";
            getline(cin, nuevo.nombre);

            cout << "Cedula: ";
            getline(cin, nuevo.cedula);

            int estadoOpcion;
            while (true) {
                cout << "Estado (1- Revision, 2- Reparacion, 3- Barado): ";
                cin >> estadoOpcion;
                if (!cin.fail() && (estadoOpcion >= 1 && estadoOpcion <= 3)) {
                    if (estadoOpcion == 1) nuevo.estado = "Revision";
                    if (estadoOpcion == 2) nuevo.estado = "Reparacion";
                    if (estadoOpcion == 3) nuevo.estado = "Barado";
                    limpiarEntrada();
                    break;
                }
                else {
                    cout << "[ERROR] Opcion de estado invalida. Intente de nuevo.\n";
                    limpiarEntrada();
                }
            }

            cout << "Telefono: ";
            getline(cin, nuevo.telefono);

            cout << "Fecha de entrada: ";
            getline(cin, nuevo.fechaEntrada);

            cout << "Detalle inicial de la falla: ";
            getline(cin, nuevo.detalle);

            nuevo.repuestosAsignados = "Ninguno";
            nuevo.totalPagar = 0.0;

            listaClientes.push_back(nuevo);
            cout << "\n¡Cliente registrado con exito!\n";
            break;
        }
        case 2: {
            
            cout << "\n--- ACTUALIZACION DE ESTADO ---\n";
            if (listaClientes.empty()) {
                cout << "[ALERTA] No hay clientes registrados.\n";
                break;
            }

            string cedulaBuscar;
            cout << "Ingrese la cedula del cliente: ";
            getline(cin, cedulaBuscar);

            bool encontrado = false;
            for (size_t i = 0; i < listaClientes.size(); ++i) {
                if (listaClientes[i].cedula == cedulaBuscar) {
                    encontrado = true;
                    cout << "Cliente: " << listaClientes[i].nombre << " | Estado actual: " << listaClientes[i].estado << "\n";

                    int nuevoEstadoOp;
                    while (true) {
                        cout << "Nuevo Estado (1- Revision, 2- Reparacion, 3- Barado): ";
                        cin >> nuevoEstadoOp;
                        if (!cin.fail() && (nuevoEstadoOp >= 1 && nuevoEstadoOp <= 3)) {
                            if (nuevoEstadoOp == 1) listaClientes[i].estado = "Revision";
                            if (nuevoEstadoOp == 2) listaClientes[i].estado = "Reparacion";
                            if (nuevoEstadoOp == 3) listaClientes[i].estado = "Barado";
                            limpiarEntrada();
                            cout << "¡Estado actualizado!\n";
                            break;
                        }
                        else {
                            cout << "[ERROR] Seleccion invalida. Intente de nuevo.\n";
                            limpiarEntrada();
                        }
                    }
                    break;
                }
            }
            if (!encontrado) cout << "[ALERTA] No se encontro la cedula.\n";
            break;
        }
        case 3: {
            
            cout << "\n--- ASIGNAR PRODUCTO O REPUESTO DE MOTOR ---\n";
            if (listaClientes.empty()) {
                cout << "[ALERTA] No hay clientes registrados.\n";
                break;
            }

            string cedulaBuscar;
            cout << "Ingrese la cedula del cliente: ";
            getline(cin, cedulaBuscar);

            bool clienteEncontrado = false;
            for (size_t i = 0; i < listaClientes.size(); ++i) {
                if (listaClientes[i].cedula == cedulaBuscar) {
                    clienteEncontrado = true;
                    cout << "Cliente encontrado: " << listaClientes[i].nombre << "\n";

                    int codigoBuscar;
                    cout << "Ingrese el CODIGO del repuesto a utilizar: ";
                    cin >> codigoBuscar;

                    if (cin.fail()) {
                        cout << "[ERROR] Codigo numerico invalido.\n";
                        limpiarEntrada();
                        break;
                    }

                    bool productoEncontrado = false;
                    for (size_t j = 0; j < catalogo.size(); ++j) {
                        if (catalogo[j].codigo == codigoBuscar) {
                            productoEncontrado = true;

                            
                            if (listaClientes[i].repuestosAsignados == "Ninguno") {
                                listaClientes[i].repuestosAsignados = catalogo[j].nombre;
                            }
                            else {
                                listaClientes[i].repuestosAsignados += " + " + catalogo[j].nombre;
                            }

                            
                            listaClientes[i].detalle += " (Se instalo: " + catalogo[j].nombre + ")";

                            
                            listaClientes[i].totalPagar += catalogo[j].precioColones;

                            cout << "\n>> ¡" << catalogo[j].nombre << " agregado con éxito!\n";
                            cout << ">> Monto: c" << fixed << setprecision(2) << catalogo[j].precioColones << " agregados al cobro.\n";
                            break;
                        }
                    }
                    if (!productoEncontrado) {
                        cout << "[ERROR] El codigo de repuesto no existe en el catalogo.\n";
                    }
                    limpiarEntrada();
                    break;
                }
            }
            if (!clienteEncontrado) cout << "[ALERTA] No se encontro al cliente con esa cedula.\n";
            break;
        }
        case 4: {
            
            cout << "\n====================================================================\n";
            cout << "            CATALOGO GENERAL Y REPUESTOS DE MOTOR (c)               \n";
            cout << "====================================================================\n";
            cout << left << setw(10) << "CODIGO" << setw(42) << "REPUESTO / PRODUCTO" << "PRECIO (c)\n";
            cout << "--------------------------------------------------------------------\n";
            for (size_t i = 0; i < catalogo.size(); ++i) {
                cout << left << setw(10) << catalogo[i].codigo
                    << setw(42) << catalogo[i].nombre
                    << "c" << fixed << setprecision(2) << catalogo[i].precioColones << "\n";
            }
            cout << "====================================================================\n";
            break;
        }
        case 5: {
            
            cout << "\n==================================================\n";
            cout << "           LISTA DE CLIENTES EN EL TALLER         \n";
            cout << "==================================================\n";

            if (listaClientes.empty()) {
                cout << "No hay clientes registrados en este momento.\n";
            }
            else {
                for (size_t i = 0; i < listaClientes.size(); ++i) {
                    cout << "Cliente #" << (i + 1) << "\n";
                    cout << "  Placa:            " << listaClientes[i].placa << "\n";
                    cout << "  Nombre:           " << listaClientes[i].nombre << "\n";
                    cout << "  Cedula:           " << listaClientes[i].cedula << "\n";
                    cout << "  Estado:           " << listaClientes[i].estado << "\n";
                    cout << "  Telefono:         " << listaClientes[i].telefono << "\n";
                    cout << "  Fecha de Entrada: " << listaClientes[i].fechaEntrada << "\n";
                    cout << "  Historial/Detalle:" << listaClientes[i].detalle << "\n";
                    cout << "  Piezas de Motor:  " << listaClientes[i].repuestosAsignados << "\n";
                    cout << "  TOTAL FACTURADO:  " << "c" << fixed << setprecision(2) << listaClientes[i].totalPagar << "\n";
                    cout << "--------------------------------------------------\n";
                }
            }
            break;
        }
        default:
            cout << "\n[ALERTA] Opcion no valida. Elija un numero entre 1 y 6.\n";
            break;
        }
    }

    return 0;
}
