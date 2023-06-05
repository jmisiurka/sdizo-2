#include <iostream>
#include <chrono>
#include <random>
#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"

void mst_menu();

void shortpath_menu();

void maximum_flow_menu();

void mst_tests();

void shortpath_tests();

void maximum_flow_tests();

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
    AdjacencyMatrix *matrix = nullptr;
    AdjacencyList *list = nullptr;

    const std::string MST_TEXT = "Wybierz jedną z opcji:\n"
                                 "\t1. Wczytaj graf z pliku\n"
                                 "\t2. Wygeneruj losowy graf\n"
                                 "\t3. Wyświetl graf\n"
                                 "\t4. Algorytm Prima\n"
                                 "\t5. Algorytm Kruskala\n"
                                 "\t6. Testy\n"
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
                delete matrix;
                delete list;

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
                if (matrix == nullptr || list == nullptr)
                {
                    matrix = new AdjacencyMatrix(0);
                    list = new AdjacencyList(0);
                }

                std::cout << "Podaj wielkość grafu do utworzenia:" << std::endl;
                int graphV;
                std::cin >> graphV;
                while (std::cin.fail())
                {   //sprawdzenie czy dane wejściowe są poprawne
                    std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

                    std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');    //wyczyszczenie bufora wejścia

                    std::cout << "Podaj wielkość grafu do utworzenia:" << std::endl;

                    std::cin >> graphV;         //ponowne pobranie opcji od użytkownika
                }

                std::cout << "Podaj minimalną wagę krawędzi:" << std::endl;
                int minWeight;
                std::cin >> minWeight;
                while (std::cin.fail())
                {   //sprawdzenie czy dane wejściowe są poprawne
                    std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

                    std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');    //wyczyszczenie bufora wejścia

                    std::cout << "Podaj minimalną wagę krawędzi:" << std::endl;

                    std::cin >> minWeight;         //ponowne pobranie opcji od użytkownika
                }

                std::cout << "Podaj maksymalną wagę krawędzi:" << std::endl;
                int maxWeight;
                std::cin >> maxWeight;
                while (std::cin.fail())
                {   //sprawdzenie czy dane wejściowe są poprawne
                    std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

                    std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');    //wyczyszczenie bufora wejścia

                    std::cout << "Podaj maksymalną wagę krawędzi:" << std::endl;

                    std::cin >> maxWeight;         //ponowne pobranie opcji od użytkownika
                }

                std::cout << "Skierowany?\n"
                             "\t1. Tak\n"
                             "\t2. Nie\n";
                int directed;
                std::cin >> directed;
                while (std::cin.fail())
                {   //sprawdzenie czy dane wejściowe są poprawne
                    std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

                    std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');    //wyczyszczenie bufora wejścia

                    std::cout << "Skierowany?\n"
                                 "\t1. Tak\n"
                                 "\t2. Nie\n";

                    std::cin >> directed;         //ponowne pobranie opcji od użytkownika
                }

                std::cout << "Gęstość grafu:\n"
                             "\t1. 20%\n"
                             "\t2. 60%\n"
                             "\t3. 99%\n";
                int densityLevel;
                std::cin >> densityLevel;
                while (std::cin.fail())
                {   //sprawdzenie czy dane wejściowe są poprawne
                    std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

                    std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');    //wyczyszczenie bufora wejścia

                    std::cout << "Gęstość grafu:\n"
                                 "\t1. 20%\n"
                                 "\t2. 60%\n"
                                 "\t3. 99%\n";

                    std::cin >> densityLevel;         //ponowne pobranie opcji od użytkownika
                }

                matrix->generateRandomGraph(graphV, directed == 1, minWeight, maxWeight, densityLevel);
                list->copyFromMatrix(*matrix);
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
            case 6:
            {
                mst_tests();
            }
            default:
                std::cout << "Nie rozpoznano opcji" << std::endl;
        }


    } while (choice != 0);
}

void shortpath_menu()
{
    AdjacencyMatrix *matrix = nullptr;
    AdjacencyList *list = nullptr;
    int startingVertex = -1;                //domyślnie brak, ale może być wczytany z pliku

    const std::string SHORTPATH_TEXT = "Wybierz jedną z opcji:\n"
                                       "\t1. Wczytaj graf z pliku\n"
                                       "\t2. Wygeneruj losowy graf\n"
                                       "\t3. Wyświetl graf\n"
                                       "\t4. Algorytm Dijkstry\n"
                                       "\t5. Algorytm Bellmana-Forda\n"
                                       "\t6. Testy\n"
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
                delete matrix;
                delete list;

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
            {
                if (matrix == nullptr || list == nullptr)
                {
                    matrix = new AdjacencyMatrix(0);
                    list = new AdjacencyList(0);
                }

                std::cout << "Podaj wielkość grafu do utworzenia:" << std::endl;
                int graphV;
                std::cin >> graphV;
                while (std::cin.fail())
                {   //sprawdzenie czy dane wejściowe są poprawne
                    std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

                    std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');    //wyczyszczenie bufora wejścia

                    std::cout << "Podaj wielkość grafu do utworzenia:" << std::endl;

                    std::cin >> graphV;         //ponowne pobranie opcji od użytkownika
                }

                std::cout << "Podaj minimalną wagę krawędzi:" << std::endl;
                int minWeight;
                std::cin >> minWeight;
                while (std::cin.fail())
                {   //sprawdzenie czy dane wejściowe są poprawne
                    std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

                    std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');    //wyczyszczenie bufora wejścia

                    std::cout << "Podaj minimalną wagę krawędzi:" << std::endl;

                    std::cin >> minWeight;         //ponowne pobranie opcji od użytkownika
                }

                std::cout << "Podaj maksymalną wagę krawędzi:" << std::endl;
                int maxWeight;
                std::cin >> maxWeight;
                while (std::cin.fail())
                {   //sprawdzenie czy dane wejściowe są poprawne
                    std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

                    std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');    //wyczyszczenie bufora wejścia

                    std::cout << "Podaj maksymalną wagę krawędzi:" << std::endl;

                    std::cin >> maxWeight;         //ponowne pobranie opcji od użytkownika
                }

                std::cout << "Skierowany?\n"
                             "\t1. Tak\n"
                             "\t2. Nie\n";
                int directed;
                std::cin >> directed;
                while (std::cin.fail())
                {   //sprawdzenie czy dane wejściowe są poprawne
                    std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

                    std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');    //wyczyszczenie bufora wejścia

                    std::cout << "Skierowany?\n"
                                 "\t1. Tak\n"
                                 "\t2. Nie\n";

                    std::cin >> directed;         //ponowne pobranie opcji od użytkownika
                }

                std::cout << "Gęstość grafu:\n"
                             "\t1. 20%\n"
                             "\t2. 60%\n"
                             "\t3. 99%\n";
                int densityLevel;
                std::cin >> densityLevel;
                while (std::cin.fail())
                {   //sprawdzenie czy dane wejściowe są poprawne
                    std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

                    std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');    //wyczyszczenie bufora wejścia

                    std::cout << "Gęstość grafu:\n"
                                 "\t1. 20%\n"
                                 "\t2. 60%\n"
                                 "\t3. 99%\n";

                    std::cin >> densityLevel;         //ponowne pobranie opcji od użytkownika
                }

                matrix->generateRandomGraph(graphV, directed == 1, minWeight, maxWeight, densityLevel);
                list->copyFromMatrix(*matrix);
                break;
            }
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
                matrix->shortpath_Dijkstra(0);
                list->shortpath_Dijkstra(0);

                break;
            }
            case 5:
            {
                if (matrix == nullptr || list == nullptr)
                {
                    std::cout << "Nie załadowano grafu" << std::endl;
                    break;
                }
                matrix->shortpath_BF(startingVertex);
                list->shortpath_BF(startingVertex);
                break;
            }
            case 6:
            {
                shortpath_tests();
            }
            default:
                std::cout << "Nie rozpoznano opcji" << std::endl;
        }


    } while (choice != 0);
}

void maximum_flow_menu()
{
    AdjacencyMatrix *matrix = nullptr;
    AdjacencyList *list = nullptr;
    int vertices[] = {-1, -1};                //domyślnie brak, ale mogą być wczytane z pliku

    const std::string MAXIMUM_FLOW_MENU = "Wybierz jedną z opcji:\n"
                                          "\t1. Wczytaj graf z pliku\n"
                                          "\t2. Wygeneruj losowy graf\n"
                                          "\t3. Wyświetl graf\n"
                                          "\t4. Algorytm Forda-Fulkersona z BFS\n"
                                          "\t5. Algorytm Forda-Fulkersona z DFS\n"
                                          "\t6. Testy\n"
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
                delete matrix;
                delete list;

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
            {
                if (matrix == nullptr || list == nullptr)
                {
                    matrix = new AdjacencyMatrix(0);
                    list = new AdjacencyList(0);
                }

                std::cout << "Podaj wielkość grafu do utworzenia:" << std::endl;
                int graphV;
                std::cin >> graphV;
                while (std::cin.fail())
                {   //sprawdzenie czy dane wejściowe są poprawne
                    std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

                    std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');    //wyczyszczenie bufora wejścia

                    std::cout << "Podaj wielkość grafu do utworzenia:" << std::endl;

                    std::cin >> graphV;         //ponowne pobranie opcji od użytkownika
                }

                std::cout << "Podaj minimalną wagę krawędzi:" << std::endl;
                int minWeight;
                std::cin >> minWeight;
                while (std::cin.fail())
                {   //sprawdzenie czy dane wejściowe są poprawne
                    std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

                    std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');    //wyczyszczenie bufora wejścia

                    std::cout << "Podaj minimalną wagę krawędzi:" << std::endl;

                    std::cin >> minWeight;         //ponowne pobranie opcji od użytkownika
                }

                std::cout << "Podaj maksymalną wagę krawędzi:" << std::endl;
                int maxWeight;
                std::cin >> maxWeight;
                while (std::cin.fail())
                {   //sprawdzenie czy dane wejściowe są poprawne
                    std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

                    std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');    //wyczyszczenie bufora wejścia

                    std::cout << "Podaj maksymalną wagę krawędzi:" << std::endl;

                    std::cin >> maxWeight;         //ponowne pobranie opcji od użytkownika
                }

                std::cout << "Skierowany?\n"
                             "\t1. Tak\n"
                             "\t2. Nie\n";
                int directed;
                std::cin >> directed;
                while (std::cin.fail())
                {   //sprawdzenie czy dane wejściowe są poprawne
                    std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

                    std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');    //wyczyszczenie bufora wejścia

                    std::cout << "Skierowany?\n"
                                 "\t1. Tak\n"
                                 "\t2. Nie\n";

                    std::cin >> directed;         //ponowne pobranie opcji od użytkownika
                }

                std::cout << "Gęstość grafu:\n"
                             "\t1. 20%\n"
                             "\t2. 60%\n"
                             "\t3. 99%\n";
                int densityLevel;
                std::cin >> densityLevel;
                while (std::cin.fail())
                {   //sprawdzenie czy dane wejściowe są poprawne
                    std::cout << "Podano nieprawidłowe dane wejściowe\n\n";

                    std::cin.clear();       //usunięcie flagi niepoprawnych danych wejściowych w strumieniu wejścia
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                    '\n');    //wyczyszczenie bufora wejścia

                    std::cout << "Gęstość grafu:\n"
                                 "\t1. 20%\n"
                                 "\t2. 60%\n"
                                 "\t3. 99%\n";

                    std::cin >> densityLevel;         //ponowne pobranie opcji od użytkownika
                }

                matrix->generateRandomGraph(graphV, directed == 1, minWeight, maxWeight, densityLevel);
                list->copyFromMatrix(*matrix);
                break;
            }
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
                list->Ford_Fulkerson(vertices[0], vertices[1], 2);
                break;
            }
            case 6:
            {
                maximum_flow_tests();
            }
            default:
                std::cout << "Nie rozpoznano opcji" << std::endl;
        }


    } while (choice != 0);
}

void mst_tests()
{
    /***********************
     * KONFIGURACJA TESTÓW *
    ***********************/
    const int testPoints = 7;
    const int tests = 50;
    const int graphSizes[] = {60, 80, 100, 120, 140, 160, 180};
    /**********************
     * KONIEC KONFIGURACJI
     **********************/

    AdjacencyMatrix matrix = AdjacencyMatrix(0);
    AdjacencyList list = AdjacencyList(0);

    std::chrono::duration<double> times[4][7][3];

    for (int i = 0; i < testPoints; i++)        //7 różnych wielkości grafu
    {
        for (int j = 0; j < 3; j++)            //3 gęstości grafu
        {
            std::chrono::duration<double> matrixPrimTime = std::chrono::duration<double>::zero();
            std::chrono::duration<double> matrixKruskalTime = std::chrono::duration<double>::zero();
            std::chrono::duration<double> listPrimTime = std::chrono::duration<double>::zero();
            std::chrono::duration<double> listKruskalTime = std::chrono::duration<double>::zero();
            for (int k = 0; k < tests; k++)
            {
                matrix.generateRandomGraph(graphSizes[i], false, 1, 50, j+1);
                list.copyFromMatrix(matrix);

                //prim na macierzy
                std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
                matrix.MST_Prim(0, true);
                std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
                matrixPrimTime += std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

                //prim na liście
                t1 = std::chrono::high_resolution_clock::now();
                list.MST_Prim(0, true);
                t2 = std::chrono::high_resolution_clock::now();
                listPrimTime += std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

                //kruskal na macierzy
                t1 = std::chrono::high_resolution_clock::now();
                matrix.MST_Kruskal(true);
                t2 = std::chrono::high_resolution_clock::now();
                matrixKruskalTime += std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

                //kruskal na liście
                t1 = std::chrono::high_resolution_clock::now();
                list.MST_Kruskal(true);
                t2 = std::chrono::high_resolution_clock::now();
                listKruskalTime += std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

                std::cout << "V: " << graphSizes[i] << ", poziom gęstości: " << j + 1 << ", iteracja: " << k << std::endl;
            }

            times[0][i][j] = matrixPrimTime / 50.0f;
            times[1][i][j] = listPrimTime / 50.0f;
            times[2][i][j] = matrixKruskalTime / 50.0f;
            times[3][i][j] = listKruskalTime / 50.0f;
        }
    }

    std::ofstream output("mst_tests.csv");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 7; k++)
            {
                output << graphSizes[k] << "; " << j + 1 << "; " << times[i][k][j].count() << std::endl;
            }
        }
        output << std::endl << std::endl;
    }
}

void shortpath_tests()
{
    /***********************
     * KONFIGURACJA TESTÓW *
    ***********************/
    const int testPoints = 7;
    const int tests = 50;
    const int graphSizes[] = {60, 100, 140, 180, 220, 260, 300};
    /**********************
     * KONIEC KONFIGURACJI
     **********************/

    AdjacencyMatrix matrix = AdjacencyMatrix(0);
    AdjacencyList list = AdjacencyList(0);

    std::chrono::duration<double> times[4][7][3];

    for (int i = 0; i < testPoints; i++)        //7 różnych wielkości grafu
    {
        for (int j = 0; j < 3; j++)            //3 gęstości grafu
        {
            std::chrono::duration<double> matrixDijkstraTime = std::chrono::duration<double>::zero();
            std::chrono::duration<double> matrixBFTime = std::chrono::duration<double>::zero();
            std::chrono::duration<double> listDijkstraTime = std::chrono::duration<double>::zero();
            std::chrono::duration<double> listBFTime = std::chrono::duration<double>::zero();
            for (int k = 0; k < tests; k++)
            {
                matrix.generateRandomGraph(graphSizes[i], false, 1, 50, j+1);
                list.copyFromMatrix(matrix);

                //Dijkstra na macierzy
                std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
                matrix.shortpath_Dijkstra(0, true);
                std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
                matrixDijkstraTime += std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

                //Dijkstra na liście
                t1 = std::chrono::high_resolution_clock::now();
                list.shortpath_Dijkstra(0, true);
                t2 = std::chrono::high_resolution_clock::now();
                listDijkstraTime += std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

                //Bellman-Ford na macierzy
                t1 = std::chrono::high_resolution_clock::now();
                matrix.shortpath_BF(0, true);
                t2 = std::chrono::high_resolution_clock::now();
                matrixBFTime += std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

                //Bellman-Ford na liście
                t1 = std::chrono::high_resolution_clock::now();
                list.shortpath_BF(0, true);
                t2 = std::chrono::high_resolution_clock::now();
                listBFTime += std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

                std::cout << "V: " << graphSizes[i] << ", poziom gęstości: " << j + 1 << ", iteracja: " << k << std::endl;
            }

            times[0][i][j] = matrixDijkstraTime / 50.0f;
            times[1][i][j] = listDijkstraTime / 50.0f;
            times[2][i][j] = matrixBFTime / 50.0f;
            times[3][i][j] = listBFTime / 50.0f;
        }
    }

    std::ofstream output("shortpath_tests.csv");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 7; k++)
            {
                output << graphSizes[k] << "; " << j + 1 << "; " << times[i][k][j].count() << std::endl;
            }
        }
        output << std::endl << std::endl;
    }
}

void maximum_flow_tests()
{
    /***********************
     * KONFIGURACJA TESTÓW *
    ***********************/
    const int testPoints = 7;
    const int tests = 50;
    const int graphSizes[] = {20, 30, 40, 50, 60, 70, 80};
    /**********************
     * KONIEC KONFIGURACJI
     **********************/

    AdjacencyMatrix matrix = AdjacencyMatrix(0);
    AdjacencyList list = AdjacencyList(0);

    std::default_random_engine rng(
            std::chrono::system_clock::now().time_since_epoch().count());    //generator liczb pseudolosowych
    std::uniform_int_distribution<int> random_int;

    std::chrono::duration<double> times[4][7][3];

    for (int i = 0; i < testPoints; i++)        //7 różnych wielkości grafu
    {
        for (int j = 0; j < 3; j++)            //3 gęstości grafu
        {
            std::chrono::duration<double> BFSMatrixTime = std::chrono::duration<double>::zero();
            std::chrono::duration<double> BFSListTime = std::chrono::duration<double>::zero();
            std::chrono::duration<double> DFSMatrixTime = std::chrono::duration<double>::zero();
            std::chrono::duration<double> DFSListTime = std::chrono::duration<double>::zero();
            for (int k = 0; k < tests; k++)
            {
                matrix.generateRandomGraph(graphSizes[i], false, 1, 50, j+1);
                list.copyFromMatrix(matrix);

                //Dijkstra na macierzy
                std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
                matrix.Ford_Fulkerson(0, random_int(rng) % graphSizes[i], 1, true);
                std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
                BFSMatrixTime += std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

                //Dijkstra na liście
                t1 = std::chrono::high_resolution_clock::now();
                list.Ford_Fulkerson(0, random_int(rng) % graphSizes[i], 1, true);
                t2 = std::chrono::high_resolution_clock::now();
                DFSMatrixTime += std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

                //Bellman-Ford na macierzy
                t1 = std::chrono::high_resolution_clock::now();
                matrix.Ford_Fulkerson(0, random_int(rng) % graphSizes[i], 2, true);
                t2 = std::chrono::high_resolution_clock::now();
                BFSListTime += std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

                //Bellman-Ford na liście
                t1 = std::chrono::high_resolution_clock::now();
                list.Ford_Fulkerson(0, random_int(rng) % graphSizes[i], 2, true);
                t2 = std::chrono::high_resolution_clock::now();
                DFSListTime += std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

                std::cout << "V: " << graphSizes[i] << ", poziom gęstości: " << j + 1 << ", iteracja: " << k << std::endl;
            }

            times[0][i][j] = BFSMatrixTime / 50.0f;
            times[1][i][j] = DFSMatrixTime / 50.0f;
            times[2][i][j] = BFSListTime / 50.0f;
            times[3][i][j] = DFSListTime / 50.0f;
        }
    }

    std::ofstream output("maximum_flow_tests.csv");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 7; k++)
            {
                output << graphSizes[k] << "; " << j + 1 << "; " << times[i][k][j].count() << std::endl;
            }
        }
        output << std::endl << std::endl;
    }
}