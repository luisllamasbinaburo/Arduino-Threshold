# Librería Arduino Threshold
La librería Threshold implementa un umbral para el control todo o nada con Arduino. Es posible emplear un umbral de consigna única o de doble consigna. <br />
Más información https://www.luisllamas.es/libreria-arduino-threshold/

## Instrucciones de uso
La consigna permite filtrar una señal, activando o desactivando un estado cuando el valor atraviesa las consignas. La siguiente imagen muestra el comportamiento con doble consigna. <br />
La librería resulta adecuada, por ejemplo, para activar un generador de calor en función de la temperatura registrada, un equipo de bombeo cuando la cota de un depósito supera un nivel, encender una luz o alarma cuando una variable sea superior (o inferior) a una consigna. <br />
Disponer de doble consigna filtra el ruido, reduciendo el número de encendidos de un actuador. No obstante, también es posible emplear la clase Threshold para casos de umbral con consigna única. <br />
El ciclo de histéresis empleado es positivo, es decir, el estado es HIGH cuando la variable supera el RisingThreshold. Tendréis que ser consecuentes con las acciones empleadas (por ejemplo, es diferente activar un generador de calor, o un ventilador). <br />
La clase dispone de un método AddValue, para introducir el nuevo valor de estado de entrada. De esta forma podemos usar la librería con cualquier método de entrada, incluido GPIO, interrupciones, valores calculados, o recibidos por cualquier medio de comunicación. <br />
La librería permite añadir funciones de callback para los eventos OnRising, OnFalling y OnChanging, por lo que podemos emplear la propia clase para gestionar el flujo del programa, sin tener que realizar estas tareas desde el bucle principal. <br />

### Constructor
El filtro de Threshold se instancia a través de uno de sus constructores.
```c++
Threshold<T>(T threshold)
Threshold<T>(T threshold, bool state)
Threshold<T>(T lowThreshold, T highThreshold)
Threshold<T>(T lowThreshold, T highThreshold, bool state);
```

### Usar filtro
```c++
// Añadir un nuevo valor al filtro y devolver el estado
bool AddValue(bool newState);

// Obtener el último estado
bool GetState() const;

// Consignas
T FallThreshold;
T RiseThreshold;

// Funciones callback
ThresholdAction OnChange;
ThresholdAction OnFalling;
ThresholdAction OnRising;
```

## Ejemplos
La librería Threshold incluye los siguientes ejemplos para ilustrar su uso.
* SingleThreshold: Ejemplo de umbral simple
* DoubleThreshold: Ejemplo de umbral doble (histéresis)
* Events: Ejemplo de funciones de callback
