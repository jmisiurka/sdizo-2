#include <iostream>
#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"
#include "Heap.h"

void mst_menu();
void shortpath_menu();
void maximum_flow_menu();

int main()
{
    const std::string MENU_TEXT = "Wybierz problem do analizy:\n"
                                  "\t1. MST\n"
                                  "\t2. Najkrótsza ścieżka\n"
                                  "\t3. Maksymalny przepływ\n"
                                  "\t0. Wyjdź\n";

    int choice;

    do
    {
        std::cout << MENU_TEXT;
        std::cin >> choice;

        while (std::cin.fail())
        {   //sprawdzenie czy dane wejściowe są poprawne
            std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

            std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');    //wyczyszczenie bufora wejścia

            std::cout << MENU_TEXT;

            std::cin >> choice;         //ponowne pobranie opcji od użytkownika
        }

        switch (choice)
        {
            case 0:
                return 0;
            case 1:
                mst_menu();
                break;
            case 2:
                shortpath_menu();
                break;
            case 3:
                maximum_flow_menu();
                break;
            default:
                std::cout << "Nie rozpoznano opcji" << std::endl;
        }


    } while (choice != 0);
}

void mst_menu()
{
    AdjacencyMatrix* matrix = nullptr;
    AdjacencyList* list = nullptr;

    const std::string MST_TEXT = "Wybierz jedną z opcji:\n"
                                  "\t1. Wczytaj graf z pliku\n"
                                  "\t2. Wygeneruj losowy graf\n"
                                  "\t3. Wyświetl graf\n"
                                  "\t4. Algorytm Prima\n"
                                  "\t5. Algorytm Kruskala\n"
                                  "\t0. Wyjdź\n";

    int choice;

    do
    {
        std::cout << MST_TEXT;
        std::cin >> choice;

        while (std::cin.fail())
        {   //sprawdzenie czy dane wejściowe są poprawne
            std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

            std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');    //wyczyszczenie bufora wejścia

            std::cout << MST_TEXT;

            std::cin >> choice;         //ponowne pobranie opcji od użytkownika
        }

        switch (choice)
        {
            case 0:
                if (matrix != nullptr)
                {
                    delete matrix;
                }

                if (list != nullptr)
                {
                    delete list;
                }

                return;
            case 1:
            {
                std::cout << "Podaj nazwę pliku do wczytania grafu:" << std::endl;
                std::string filename;

                std::cin >> filename;
                while (std::cin.fail())
                {   //sprawdzenie czy dane wejściowe są poprawne
                    std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

                    std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');    //wyczyszczenie bufora wejścia

                    std::cout << "Podaj nazwę pliku do wczytania grafu:" << std::endl;

                    std::cin >> filename;         //ponowne pobranie opcji od użytkownika
                }

                if (matrix == nullptr || list == nullptr)
                {
                    matrix = new AdjacencyMatrix(0);
                    list = new AdjacencyList(0);
                }

                matrix->loadFromFile(filename, 0, nullptr);
                list->loadFromFile(filename, 0, nullptr);

                matrix->print();
                list->print();
                break;
            }
            case 2:
                //TODO losowa generacja
                break;
            case 3:
                if (matrix == nullptr || list == nullptr)
                {
                    std::cout << "Nie załadowano grafu" << std::endl;
                    break;
                }
                matrix->print();
                list->print();
                break;
            case 4:
            {
                if (matrix == nullptr || list == nullptr)
                {
                    std::cout << "Nie załadowano grafu" << std::endl;
                    break;
                }
                matrix->MST_Prim(0);
                list->MST_Prim(0);

                break;
            }
            case 5:
            {
                if (matrix == nullptr || list == nullptr)
                {
                    std::cout << "Nie załadowano grafu" << std::endl;
                    break;
                }
                matrix->MST_Kruskal();
                list->MST_Kruskal();
                break;
            }
            default:
                std::cout << "Nie rozpoznano opcji" << std::endl;
        }


    } while (choice != 0);
}

void shortpath_menu()
{
    AdjacencyMatrix* matrix = nullptr;
    AdjacencyList* list = nullptr;
    int startingVertex = -1;                //domyślnie brak, ale może być wczytany z pliku

    const std::string SHORTPATH_TEXT = "Wybierz jedną z opcji:\n"
                                 "\t1. Wczytaj graf z pliku\n"
                                 "\t2. Wygeneruj losowy graf\n"
                                 "\t3. Wyświetl graf\n"
                                 "\t4. Algorytm Dijkstry\n"
                                 "\t5. Algorytm Bellmana-Forda\n"
                                 "\t0. Wyjdź\n";

    int choice;

    do
    {
        std::cout << SHORTPATH_TEXT;
        std::cin >> choice;

        while (std::cin.fail())
        {   //sprawdzenie czy dane wejściowe są poprawne
            std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

            std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');    //wyczyszczenie bufora wejścia

            std::cout << SHORTPATH_TEXT;

            std::cin >> choice;         //ponowne pobranie opcji od użytkownika
        }

        switch (choice)
        {
            case 0:
                if (matrix != nullptr)
                {
                    delete matrix;
                }

                if (list != nullptr)
                {
                    delete list;
                }

                return;
            case 1:
            {
                std::cout << "Podaj nazwę pliku do wczytania grafu:" << std::endl;
                std::string filename;

                std::cin >> filename;
                while (std::cin.fail())
                {   //sprawdzenie czy dane wejściowe są poprawne
                    std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

                    std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');    //wyczyszczenie bufora wejścia

                    std::cout << "Podaj nazwę pliku do wczytania grafu:" << std::endl;

                    std::cin >> filename;         //ponowne pobranie opcji od użytkownika
                }

                if (matrix == nullptr || list == nullptr)
                {
                    matrix = new AdjacencyMatrix(0);
                    list = new AdjacencyList(0);
                }

                matrix->loadFromFile(filename, 1, &startingVertex);
                list->loadFromFile(filename, 1, &startingVertex);

                matrix->print();
                list->print();
                break;
            }
            case 2:
                //TODO losowa generacja
                break;
            case 3:
                if (matrix == nullptr || list == nullptr)
                {
                    std::cout << "Nie załadowano grafu" << std::endl;
                    break;
                }
                matrix->print();
                list->print();
                break;
            case 4:
            {
                if (matrix == nullptr || list == nullptr)
                {
                    std::cout << "Nie załadowano grafu" << std::endl;
                    break;
                }
                matrix->Shortpath_Dijkstra(0);
                list->Shortpath_Dijkstra(0);

                break;
            }
            case 5:
            {
                if (matrix == nullptr || list == nullptr)
                {
                    std::cout << "Nie załadowano grafu" << std::endl;
                    break;
                }
                matrix->Shortpath_BF(startingVertex);
                list->Shortpath_BF(startingVertex);
                break;
            }
            default:
                std::cout << "Nie rozpoznano opcji" << std::endl;
        }


    } while (choice != 0);
}

void maximum_flow_menu()
{
    AdjacencyMatrix* matrix = nullptr;
    AdjacencyList* list = nullptr;
    int vertices[] = {-1, -1};                //domyślnie brak, ale mogą być wczytane z pliku

    const std::string MAXIMUM_FLOW_MENU = "Wybierz jedną z opcji:\n"
                                       "\t1. Wczytaj graf z pliku\n"
                                       "\t2. Wygeneruj losowy graf\n"
                                       "\t3. Wyświetl graf\n"
                                       "\t4. Algorytm Forda-Fulkersona z BFS\n"
                                       "\t5. Algorytm Forda-Fulkersona z DFS\n"
                                       "\t0. Wyjdź\n";

    int choice;

    do
    {
        std::cout << MAXIMUM_FLOW_MENU;
        std::cin >> choice;

        while (std::cin.fail())
        {   //sprawdzenie czy dane wejściowe są poprawne
            std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

            std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');    //wyczyszczenie bufora wejścia

            std::cout << MAXIMUM_FLOW_MENU;

            std::cin >> choice;         //ponowne pobranie opcji od użytkownika
        }

        switch (choice)
        {
            case 0:
                if (matrix != nullptr)
                {
                    delete matrix;
                }

                if (list != nullptr)
                {
                    delete list;
                }

                return;
            case 1:
            {
                std::cout << "Podaj nazwę pliku do wczytania grafu:" << std::endl;
                std::string filename;

                std::cin >> filename;
                while (std::cin.fail())
                {   //sprawdzenie czy dane wejściowe są poprawne
                    std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

                    std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');    //wyczyszczenie bufora wejścia

                    std::cout << "Podaj nazwę pliku do wczytania grafu:" << std::endl;

                    std::cin >> filename;         //ponowne pobranie opcji od użytkownika
                }

                if (matrix == nullptr || list == nullptr)
                {
                    matrix = new AdjacencyMatrix(0);
                    list = new AdjacencyList(0);
                }

                matrix->loadFromFile(filename, 2, vertices);
                list->loadFromFile(filename, 2, vertices);

                matrix->print();
                list->print();
                break;
            }
            case 2:
                //TODO losowa generacja
                break;
            case 3:
                if (matrix == nullptr || list == nullptr)
                {
                    std::cout << "Nie załadowano grafu" << std::endl;
                    break;
                }
                matrix->print();
                list->print();
                break;
            case 4:
            {
                if (matrix == nullptr || list == nullptr)
                {
                    std::cout << "Nie załadowano grafu" << std::endl;
                    break;
                }
                matrix->Ford_Fulkerson(vertices[0], vertices[1], 1);
                list->Ford_Fulkerson(vertices[0], vertices[1], 1);

                break;
            }
            case 5:
            {
                if (matrix == nullptr || list == nullptr)
                {
                    std::cout << "Nie załadowano grafu" << std::endl;
                    break;
                }
                matrix->Ford_Fulkerson(vertices[0], vertices[1], 2);
                //list->Ford_Fulkerson(vertices[0], vertices[1], 2);
                break;
            }
            default:
                std::cout << "Nie rozpoznano opcji" << std::endl;
        }


    } while (choice != 0);
}