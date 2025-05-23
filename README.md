# 🔬 Secuenciador de Alineamiento Local en C++

Este proyecto implementa el algoritmo de alineamiento local (Smith-Waterman) en C++, con soporte para entrada FASTA, exportación de resultados a `.txt` y pruebas unitarias usando Google Test.

## Funcionalidades

- Carga de secuencias desde archivos `.fasta`
- Alineamiento local con penalización por gaps
- Exportación de:
  - Puntuación máxima
  - Subcadena común
  - Posiciones en ambas cadenas
  - Matriz de puntuación
  - Detección de subsecuencia repetida
