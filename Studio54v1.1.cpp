#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAX_INVITADOS = 100;
const int TICKET_INICIAL = 11100;
const string ARCHIVO_INVITADOS = "ListaInvitados.txt";

// Estructura para almacenar los datos de un invitado.
typedef struct 
    {
        int ticket;
        string nombre;
        string mail;
        string celular;
        bool confirmado;
    } tInvitado;

// Estructura para la lista de invitados.
typedef struct
    {
        tInvitado invitados[MAX_INVITADOS];
        int contador;
    } tListaInvitados;

// Prototipos de funciones.
void menu();
// NUEVAS FUNCIONES AUXILIARES PARA REDUCIR DUPLICACIÓN.
bool listaEstaVacia(const tListaInvitados &lista); // Verificación de lista vacía.
bool encontrarInvitadoPorTicket(const tListaInvitados &lista, int &pos); // Búsqueda por ticket.
void cargarInvitados(tListaInvitados &lista);
void guardarInvitados(const tListaInvitados &lista);
void crearInvitado(tListaInvitados &lista);
void leerInvitados(const tListaInvitados &lista);
void actualizarInvitado(tListaInvitados &lista);
void eliminarInvitado(tListaInvitados &lista);
void confirmarAsistencia(tListaInvitados &lista);
void mostrarInvitado(const tInvitado &invitado);
int buscarInvitado(const tListaInvitados &lista, int ticket);



int main()
    {
        menu();
        return 0;
    }

// Implementación de funciones.
void menu()
    {
        tListaInvitados lista;
        lista.contador = 0;

        cargarInvitados(lista);
        
        int opcion;
        do
            {
                cout << "\n\n==================================";
                cout << "\nSTUDIO 54 - GESTOR DE INVITACIONES\n";
                cout << "==================================\n";
                cout << "1. Agregar nuevo invitado\n";
                cout << "2. Ver listado de invitados\n";
                cout << "3. Actualizar datos de invitado\n";
                cout << "4. Eliminar invitado\n";
                cout << "5. Confirmar/Cancelar asistencia\n";
                cout << "0. Salir\n";
                cout << "==================================\n";
                cout << "Selecciona una opcion: ";
                cin >> opcion;
                cin.ignore();
                
                switch(opcion)
                    {
                        case 1:
                            crearInvitado(lista);
                            break;
                        case 2:
                            leerInvitados(lista);
                            break;
                        case 3:
                            actualizarInvitado(lista);
                            break;
                        case 4:
                            eliminarInvitado(lista);
                            break;
                        case 5:
                            confirmarAsistencia(lista);
                            break;
                        case 0:
                            guardarInvitados(lista);
                            cout << "\nDatos guardados. Nos vemos en la Fiesta!!!\n" << endl;
                            break;
                        default:
                            cout << "\nOpcion no valida. Intenta nuevamente.\n" << endl;
                    }
            } while(opcion != 0);
    }

// Función para verificar si la lista está vacía.
bool listaEstaVacia(const tListaInvitados &lista)
    {
        if (lista.contador == 0)
            {
                cout << "\nNo hay invitados registrados.\n" << endl;
                return true;
            }
        return false;
    }

// Función para encontrar invitado por ticket.
bool encontrarInvitadoPorTicket(const tListaInvitados &lista, int &pos)
    {
        int ticket;
        cout << "\nIngresa el Nro. de ticket del invitado: \n";
        cin >> ticket;
        cin.ignore();
        
        pos = buscarInvitado(lista, ticket);
        if (pos == -1)
            {
                cout << "\nNo se encontro un invitado con ese Nro. de ticket.\n" << endl;
                return false;
            }
        return true;
    }

void cargarInvitados(tListaInvitados &lista)
    {
        ifstream archivo(ARCHIVO_INVITADOS);

        if (archivo.is_open())
            {
                lista.contador = 0;
                while (lista.contador < MAX_INVITADOS && 
                    archivo >> lista.invitados[lista.contador].ticket >> ws &&
                    getline(archivo, lista.invitados[lista.contador].nombre) &&
                    getline(archivo, lista.invitados[lista.contador].mail) &&
                    getline(archivo, lista.invitados[lista.contador].celular) &&
                    archivo >> lista.invitados[lista.contador].confirmado)
                    {
                        lista.contador++;
                        archivo.ignore();
                    }
                archivo.close();
            } else
                {
                    cout << "\nNo se encontro archivo de invitados. Se creara uno nuevo.\n" << endl;
                }
    }

void guardarInvitados(const tListaInvitados &lista)
    {
        ofstream archivo(ARCHIVO_INVITADOS);

        if (archivo.is_open())
            {
                for (int i = 0; i < lista.contador; i++)
                    {
                        archivo << lista.invitados[i].ticket << endl
                                << lista.invitados[i].nombre << endl
                                << lista.invitados[i].mail << endl
                                << lista.invitados[i].celular << endl
                                << lista.invitados[i].confirmado << endl;
                    }
                archivo.close();
            } else
                {
                    cout << "\nError al guardar los datos.\n" << endl;
                }
    }

void crearInvitado(tListaInvitados &lista)
    {
        if (lista.contador < MAX_INVITADOS)
            {
                tInvitado nuevo;
                nuevo.ticket = (lista.contador == 0) ? TICKET_INICIAL : 
                            lista.invitados[lista.contador-1].ticket + 1;
                
                cout << "\nNuevo invitado - Ticket Nro: " << nuevo.ticket << endl;
                cout << "Nombre: ";
                getline(cin, nuevo.nombre);
                cout << "Email: ";
                getline(cin, nuevo.mail);
                cout << "Celular: ";
                getline(cin, nuevo.celular);
                nuevo.confirmado = false;
                
                lista.invitados[lista.contador] = nuevo;
                lista.contador++;
                
                guardarInvitados(lista);
                cout << "\nInvitado agregado exitosamente!\n" << endl;
            } else
                {
                    cout << "\nNo se pueden agregar mas invitados. Capacidad maxima alcanzada.\n" << endl;
                }
    }

void leerInvitados(const tListaInvitados &lista)
    {
        // Usando la nueva función para verificar lista vacía
        if (listaEstaVacia(lista)) return;
        
        cout << "\n*** LISTADO DE INVITADOS ***\n" << endl;
        cout << left << setw(8) << "Ticket" << setw(30) << "Nombre" 
            << setw(25) << "Email" << setw(15) << "Celular" 
            << "Estado" << endl;
        cout << string(90, '=') << endl;
        
        for (int i = 0; i < lista.contador; i++)
            {
                cout << left << setw(8) << lista.invitados[i].ticket 
                    << setw(30) << lista.invitados[i].nombre 
                    << setw(25) << lista.invitados[i].mail 
                    << setw(15) << lista.invitados[i].celular 
                    << (lista.invitados[i].confirmado ? "CONFIRMADO" : "PENDIENTE") 
                    << endl;
            }
    }

void actualizarInvitado(tListaInvitados &lista)
    {
        // Usando la nueva función para verificar lista vacía
        if (listaEstaVacia(lista)) return;
        
        int pos;
        // Usando la nueva función para buscar por ticket
        if (!encontrarInvitadoPorTicket(lista, pos)) return;

        cout << "\nActualizando datos del invitado (deja en blanco para mantener el valor actual):" << endl;
        
        cout << "Nombre actual: " << lista.invitados[pos].nombre << endl;
        cout << "Nuevo nombre: ";
        string temp;
        getline(cin, temp);
        if (!temp.empty()) lista.invitados[pos].nombre = temp;
        
        cout << "Email actual: " << lista.invitados[pos].mail << endl;
        cout << "Nuevo email: ";
        getline(cin, temp);
        if (!temp.empty()) lista.invitados[pos].mail = temp;
        
        cout << "Celular actual: " << lista.invitados[pos].celular << endl;
        cout << "Nuevo celular: ";
        getline(cin, temp);
        if (!temp.empty()) lista.invitados[pos].celular = temp;
        
        guardarInvitados(lista);
        cout << "\nDatos actualizados correctamente!\n" << endl;
    }

void eliminarInvitado(tListaInvitados &lista)
    {
        // Usando la nueva función para verificar lista vacía
        if (listaEstaVacia(lista)) return;
        
        int pos;
        // Usando la nueva función para buscar por ticket
        if (!encontrarInvitadoPorTicket(lista, pos)) return;

        cout << "\nEliminando invitado:\n" << endl;
        mostrarInvitado(lista.invitados[pos]);
        
        for (int i = pos; i < lista.contador - 1; i++)
            {
                lista.invitados[i] = lista.invitados[i + 1];
            }
        lista.contador--;
        
        guardarInvitados(lista);
        cout << "\nInvitado eliminado correctamente!\n" << endl;
    }

void confirmarAsistencia(tListaInvitados &lista)
    {
        // Usando la nueva función para verificar lista vacía
        if (listaEstaVacia(lista)) return;
        
        int pos;
        // Usando la nueva función para buscar por ticket
        if (!encontrarInvitadoPorTicket(lista, pos)) return;

        char opcion;
        cout << "\nInvitado encontrado:\n" << endl;
        mostrarInvitado(lista.invitados[pos]);
        
        cout << "\nConfirmar asistencia? (S/N): ";
        cin >> opcion;
        cin.ignore();
        
        if (toupper(opcion) == 'S')
            {
                lista.invitados[pos].confirmado = true;
                cout << "Asistencia CONFIRMADA." << endl;
            } else
                {
                    lista.invitados[pos].confirmado = false;
                    cout << "Asistencia CANCELADA." << endl;
                }
        
        guardarInvitados(lista);
    }

void mostrarInvitado(const tInvitado &invitado)
    {
        cout << "Ticket: " << invitado.ticket << endl;
        cout << "Nombre: " << invitado.nombre << endl;
        cout << "Email: " << invitado.mail << endl;
        cout << "Celular: " << invitado.celular << endl;
        cout << "Estado: " << (invitado.confirmado ? "CONFIRMADO" : "PENDIENTE") << endl;
    }

int buscarInvitado(const tListaInvitados &lista, int ticket)
    {
        for (int i = 0; i < lista.contador; i++)
            {
                if (lista.invitados[i].ticket == ticket)
                    {
                        return i;
                    }
            }
        return -1;
    }