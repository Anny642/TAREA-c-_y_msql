#include <iostream>
#include <mysql.h>
#include<string>

using namespace std;
int q_estado;

void menu();
void ingresar(int opcion, MYSQL* conectar);
void buscar(int opcion, MYSQL* conectar);
void modificar(int opcion, MYSQL* conectar);
void eliminar(int opcion, MYSQL* conectar);
void mostrar(int opcion, MYSQL* conectar);

int main()
{
    menu();
}

void menu() {
    MYSQL* conectar;
    conectar = mysql_init(0);
    conectar = mysql_real_connect(conectar, "localhost", "root", "johnlennon09", "ejemplo", 3306, NULL, 0);
    if (conectar) {
        int opcion, a = 0;
        do {
            system("cls");
            cout << "----------CRUD BASE DE DATOS----------" << endl;
            cout << "A QUE TABLA DESEA INGRESAR: " << endl;
            cout << "1. TABLA MARCAS" << endl;
            cout << "2. TABLA PRODUCTOS" << endl;
            cout << "3. SALIR DEL PROGRAMA" << endl;
            cout << "INGRESE UNA DE LAS OPCIONES: " << endl;
            cin >> opcion;

            if ((opcion == 2 || opcion == 1)) {
                do {
                    system("cls");
                    if (opcion == 2) {
                        cout << "    TABLA PRODUCTOS" << endl;
                    }
                    if (opcion == 1) {
                        cout << "      TABLA MARCA" << endl;
                    }
                    cout << "----------------------" << endl;
                    cout << "QUE DESEA HACER: " << endl << endl;
                    cout << " 1. INGRESAR DATOS" << endl;
                    cout << " 2. BUSCAR DATO" << endl;
                    cout << " 3. ACTUALIZAR DATOS" << endl;
                    cout << " 4. ELIMINAR DATOS" << endl;
                    cout << " 5. LEER LISTA DE DATOS COMPLETA" << endl;
                    cout << " 6. REGRESAR" << endl;
                    cout << " Ingrese opcion: \b\b";
                    cin >> a;
                    switch (a)
                    {
                    case 1:
                        system("cls");
                        ingresar(opcion, conectar);
                        break;
                    case 2:
                        system("cls");
                        buscar(opcion, conectar);
                        break;
                    case 3:
                        system("cls");
                        modificar(opcion, conectar);
                        break;
                    case 4:
                        system("cls");
                        eliminar(opcion, conectar);
                        break;

                    case 5:
                        system("cls");
                        mostrar(opcion, conectar);
                    }
                } while (a != 6);
            }
        } while (opcion != 3);
    }
    else {
        cout << "conexion fallida" << endl;
    }
}

void ingresar(int opcion, MYSQL* conectar) {
    string insert;
    if (opcion == 1) {
        cout << "----TABLA MARCA---" << endl;
        string marca;
        cout << "INGRESE EL NOMBRE DE LA MARCA :";
        cin.ignore();
        getline(cin, marca);
        insert = "insert into marca(marca) values('" + marca + "')";
        const char* i = insert.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "INGRESO EXITOSO..." << endl;
        }
        else
        {
            cout << "ERROR AL INGRESAR..." << endl;
        }
    }
    if (opcion == 2) {
        cout << "---TABLA PRODUCTOS----" << endl;
        string producto, descripcion;
        string idmarca, existencia;
        string precio_costo, precio_venta;
        string anio, mes, dia, hora, minutos, segundos;
        fflush(stdin);
        cout << "INGRESE NOMBRE DEL PRODUCTO: ";
        cin.ignore();
        getline(cin, producto);
        cout << "INGRESE EL ID DE LA MARCA (ESTE DEBE EXISTIR EN LA TABLA MARCA): ";
        cin >> idmarca;
        fflush(stdin);
        cout << "INGRESE LA DESCRIPCION DEL PRODUCTO: ";
        cin.ignore();
        getline(cin, descripcion);
        cout << "INGRESE EL PRECIO DE COSTO DEL PRODUCTO(UNICAMENTE CON 2 PUNTOS DECIMALES): ";
        cin >> precio_costo;
        cout << "INGRESE EL PRECIO DE VENTA DEL PRODUCTO(UNICAMENTE CON 2 PUNTOS DECIMALES): ";
        cin >> precio_venta;
        cout << "INGRESE LA CANTIDAD DE PRODUCTO QUE HAY EN EXISTENCIA: ";
        cin >> existencia;
        cout << "INGRESE LA FECHA Y HORA: " << endl;
        cout << "1. FECHA Y HORA ACTUAL INGRESE" << endl;
        cout << "2. FECHA Y HORA PERSONALIZADA INGRESE" << endl;
        int a;
        cin >> a;
        switch (a) {
        case 1:
            insert = "INSERT INTO producto (producto,idMarca,descripcion,precio_costo,precio_venta,existencia,fecha_ingreso) values('" + producto + "'," + idmarca + ",'" + descripcion + "','" + precio_costo + "','" + precio_venta + "','" + existencia + "',now())";
            break;
        case 2:
            cout << "DIA: ";
            cin >> dia;
            cout << "MES: ";
            cin >> mes;
            cout << "ANIO: ";
            cin >> anio;
            cout << "HORA: ";
            cin >> hora;
            cout << "MINUTOS: ";
            cin >> minutos;
            cout << "SEGUNDOS: ";
            cin >> segundos;
            insert = "INSERT INTO producto (producto,idMarca,descripcion,precio_costo,precio_venta,existencia,fecha_ingreso) values('" + producto + "'," + idmarca + ",'" + descripcion + "','" + precio_costo + "','" + precio_venta + "','" + existencia + "','" + anio + "-" + mes + "-" + dia + " " + hora + ":" + minutos + ":" + segundos + "')";
            break;
        default:
            cout << "OPCION NO VALIDA, SE INGRESARA FECHA Y HORA ACTUALES ";
            insert = "INSERT INTO producto (producto,idMarca,descripcion,precio_costo,precio_venta,existencia,fecha_ingreso) values('" + producto + "'," + idmarca + ",'" + descripcion + "','" + precio_costo + "','" + precio_venta + "','" + existencia + "',now())";
            break;
        }
        const char* i = insert.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "INGRESO EXITOSO..." << endl;
        }
        else
        {
            cout << "ERROR AL INGRESAR..." << endl;
        }
    }
    system("pause");
}
void buscar(int opcion, MYSQL* conectar) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    string id;
    if (opcion == 1) {
        cout << "POR FAVOR INGRESE EL ID DE LA MARCA PARA VER SU INFORMACION: ";
        cin >> id;
        consulta = "select * from marca where idmarca =" + id + ";";
        const char* c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            while (fila = mysql_fetch_row(resultado)) {
                cout << "ID MARCA  | MARCA" << endl;
                cout << fila[0] << "\t   " << fila[1] << endl;
                cout << "--------------------------------------------" << endl;
            }
        }
        else
        {
            cout << "ERROR AL CONSULTAR..." << endl;
        }
    }
    if (opcion == 2) {
        cout << "POR FAVOR INGRESE EL ID DE LA MARCA PARA VER SU INFORMACION: ";
        cin >> id;
        consulta = "select * from producto where idProducto=" + id + ";";
        const char* c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            cout << "ID PRODUCTO    | PRODUCTO\t      | ID MARCA      | DESCRIPCION          | PRECIO COSTO | PRECIO VENTA | EXISTENCIA | FECHA Y HORA" << endl;
            while (fila = mysql_fetch_row(resultado)) {
                cout << fila[0] << "\t\t" << fila[1] << "\t\t\t" << fila[2] << "\t\t" << fila[3] << "\t\t\t" << fila[4] << " \t\t" << fila[5] << "\t\t" << fila[6] << "\t" << fila[7] << endl;
            }
        }
        else
        {
            cout << "ERROR AL CONSULTAR..." << endl;
        }
    }
    system("pause");
}
void modificar(int opcion, MYSQL* conectar) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    string modificar;
    string id;
    char respuesta;
    if (opcion == 1) {
        cout << "POR FAVOR INGRESE EL ID DE LA MARCA PARA MODIFICAR SUS DATOS: ";
        cin >> id;
        consulta = "select * from marca where idmarca =" + id + ";";
        const char* c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            while (fila = mysql_fetch_row(resultado)) {
                cout << "ID MARCA  | MARCA" << endl;
                cout << fila[0] << "\t   " << fila[1] << endl;
                cout << "--------------------------------------------" << endl;
            }
            cout << "SEGURO QUE QUIERES MODIFICAR ESTE REGISTRO [S/N]" << endl;
            cin >> respuesta;
            if ((respuesta == 's') || (respuesta == 'S')) {
                string marca;
                cout << "INGRESE EL NOMBRE DE LA MARCA :";
                cin.ignore();
                getline(cin, marca);
                modificar = "update marca set marca='" + marca + "' where (idmarca='" + id + "');";
                const char* i = modificar.c_str();
                q_estado = mysql_query(conectar, i);
                if (!q_estado) {
                    cout << "MODIFICACION EXITOSA..." << endl;
                }
                else
                {
                    cout << "ERROR AL MODIFICAR..." << endl;
                }

            }
        }
        else
        {
            cout << "ERROR AL CONSULTAR..." << endl;
        }
    }
    if (opcion == 2) {
        cout << "POR FAVOR INGRESE EL ID DEL PRODUCTO PARA VER SU INFORMACION: ";
        cin >> id;
        string consulta = "select * from producto where idProducto=" + id + ";";
        const char* c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            cout << "ID PRODUCTO    | PRODUCTO\t      | ID MARCA      | DESCRIPCION          | PRECIO COSTO | PRECIO VENTA | EXISTENCIA | FECHA Y HORA" << endl;
            while (fila = mysql_fetch_row(resultado)) {
                cout << fila[0] << "\t\t" << fila[1] << "\t\t\t" << fila[2] << "\t\t" << fila[3] << "\t\t\t" << fila[4] << " \t\t" << fila[5] << "\t\t" << fila[6] << "\t" << fila[7] << endl;
            }
            cout << "SEGURO QUE QUIERES MODIFICAR ESTE REGISTRO [S/N]" << endl;
            cin >> respuesta;
            if ((respuesta == 's') || (respuesta == 'S')) {
                string producto, descripcion;
                string idmarca, existencia;
                string precio_costo, precio_venta;
                string anio, mes, dia, hora, minutos, segundos;
                fflush(stdin);
                cout << "INGRESE NOMBRE DEL PRODUCTO: ";
                cin.ignore();
                getline(cin, producto);
                cout << "INGRESE EL ID DE LA MARCA (ESTE DEBE EXISTIR EN LA TABLA MARCA): ";
                cin >> idmarca;
                fflush(stdin);
                cout << "INGRESE LA DESCRIPCION DEL PRODUCTO: ";
                cin.ignore();
                getline(cin, descripcion);
                cout << "INGRESE EL PRECIO DE COSTO DEL PRODUCTO(UNICAMENTE CON 2 PUNTOS DECIMALES): ";
                cin >> precio_costo;
                cout << "INGRESE EL PRECIO DE VENTA DEL PRODUCTO(UNICAMENTE CON 2 PUNTOS DECIMALES): ";
                cin >> precio_venta;
                cout << "INGRESE LA CANTIDAD DE PRODUCTO QUE HAY EN EXISTENCIA: ";
                cin >> existencia;
                cout << "INGRESE LA FECHA Y HORA: " << endl;
                cout << "1. FECHA Y HORA ACTUAL INGRESE" << endl;
                cout << "2. FECHA Y HORA PERSONALIZADA INGRESE" << endl;
                int a;
                cin >> a;
                switch (a) {
                case 1:
                    modificar = "UPDATE producto SET producto = '" + producto + "', idMarca = '" + idmarca + "', descripcion = '" + descripcion + "', precio_costo = '" + precio_costo + "', precio_venta = '" + precio_venta + "', existencia = '" + existencia + "', fecha_ingreso = now() WHERE (idProducto = '" + id + "');";
                    break;
                case 2:
                    cout << "DIA: ";
                    cin >> dia;
                    cout << "MES: ";
                    cin >> mes;
                    cout << "ANIO: ";
                    cin >> anio;
                    cout << "HORA: ";
                    cin >> hora;
                    cout << "MINUTOS: ";
                    cin >> minutos;
                    cout << "SEGUNDOS: ";
                    cin >> segundos;
                    modificar = "UPDATE producto SET producto = '" + producto + "', idMarca = '" + idmarca + "', descripcion = '" + descripcion + "', precio_costo = '" + precio_costo + "', precio_venta = '" + precio_venta + "', existencia = '" + existencia + "', fecha_ingreso ='" + anio + "-" + mes + "-" + dia + " " + hora + ":" + minutos + ":" + segundos + "' WHERE (idProducto = '" + id + "');";
                    break;
                default:
                    cout << "OPCION NO VALIDA, SE INGRESARA FECHA Y HORA ACTUALES ";
                    modificar = "UPDATE producto SET producto = '" + producto + "', idMarca = '" + idmarca + "', descripcion = '" + descripcion + "', precio_costo = '" + precio_costo + "', precio_venta = '" + precio_venta + "', existencia = '" + existencia + "', fecha_ingreso = now() WHERE (idProducto = '" + id + "');";
                    break;
                }
                const char* i = modificar.c_str();
                q_estado = mysql_query(conectar, i);
                if (!q_estado) {
                    cout << "MODIFICACION EXITOSA..." << endl;
                }
                else
                {
                    cout << "ERROR AL MODIFICAR..." << endl;
                }
            }
        }
        else
        {
            cout << "ERROR AL CONSULTAR..." << endl;
        }
    }
    system("pause");
}
void eliminar(int opcion, MYSQL* conectar) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    string id;
    char respuesta;
    string eliminar;
    if (opcion == 1) {
        cout << "POR FAVOR INGRESE EL ID DE LA MARCA PARA VER SU INFORMACION: ";
        cin >> id;
        consulta = "select * from marca where idmarca =" + id + ";";
        const char* c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            while (fila = mysql_fetch_row(resultado)) {
                cout << "ID MARCA  | MARCA" << endl;
                cout << fila[0] << "\t   " << fila[1] << endl;
                cout << "--------------------------------------------" << endl;

            }
            cout << "SEGURO QUE QUIERES ELIMINAR ESTE REGISTRO [S/N]" << endl;
            cin >> respuesta;
            if ((respuesta == 's') || (respuesta == 'S')) {
                eliminar = "delete  from marcas where idmarca=" + id + ";";
                const char* i = eliminar.c_str();
                q_estado = mysql_query(conectar, i);
                if (!q_estado) {
                    cout << "ELIMINACION EXITOSA..." << endl;
                }
                else
                {
                    cout << "ERROR AL ELIMINAR..." << endl;
                }
            }
        }
        else
        {
            cout << "ERROR AL CONSULTAR..." << endl;
        }
    }
    if (opcion == 2) {
        cout << "POR FAVOR INGRESE EL ID DEL PRODUCTO PARA VER SU INFORMACION: ";
        cin >> id;
        consulta = "select * from producto where idProducto=" + id + ";";
        const char* c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            cout << "ID PRODUCTO    | PRODUCTO\t      | ID MARCA      | DESCRIPCION          | PRECIO COSTO | PRECIO VENTA | EXISTENCIA | FECHA Y HORA" << endl;
            while (fila = mysql_fetch_row(resultado)) {
                cout << fila[0] << "\t\t" << fila[1] << "\t\t\t" << fila[2] << "\t\t" << fila[3] << "\t\t\t" << fila[4] << " \t\t" << fila[5] << "\t\t" << fila[6] << "\t" << fila[7] << endl;
            }
            cout << "SEGURO QUE QUIERES ELIMINAR ESTE REGISTRO [S/N]" << endl;
            cin >> respuesta;
            if ((respuesta == 's') || (respuesta == 'S')) {
                eliminar = "delete  from producto where idProducto=" + id + ";";
                const char* i = eliminar.c_str();
                q_estado = mysql_query(conectar, i);
                if (!q_estado) {
                    cout << "ELIMINACION EXITOSA..." << endl;
                }
                else
                {
                    cout << "ERROR AL ELIMINAR..." << endl;
                }
            }
        }
        else
        {
            cout << "ERROR AL CONSULTAR..." << endl;
        }
    }
    system("pause");
}
void mostrar(int opcion, MYSQL* conectar) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    if (opcion == 1) {
        string consulta = "select * from marca";
        const char* c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            cout << "ID MARCA  | MARCA" << endl;
            while (fila = mysql_fetch_row(resultado)) {
                cout << fila[0] << "\t   " << fila[1] << endl;
                cout << "--------------------------------------------" << endl;
            }
        }
        else
        {
            cout << "ERROR AL CONSULTAR..." << endl;
        }
    }
    if (opcion == 2) {
        string consulta = "select * from producto";
        const char* c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            cout << "ID PRODUCTO    | PRODUCTO\t      | ID MARCA      | DESCRIPCION          | PRECIO COSTO | PRECIO VENTA | EXISTENCIA | FECHA Y HORA" << endl;
            while (fila = mysql_fetch_row(resultado)) {
                cout << fila[0] << "\t\t" << fila[1] << "\t\t" << fila[2] << "\t\t" << fila[3] << "\t\t" << fila[4] << " \t\t" << fila[5] << "\t\t" << fila[6] << "\t" << fila[7] << endl;
            }
        }
        else
        {
            cout << "ERROR AL CONSULTAR..." << endl;
        }
    }
    system("pause");
}