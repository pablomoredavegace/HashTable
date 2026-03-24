#include "nif.h"
#include "dispersion_function.h"
#include "exploration_function.h"
#include "sequence.h"
#include "dynamic_sequence.h"
#include "static_sequence.h"
#include "hash_table.h"

#include <memory>


struct Options {
  unsigned table_size = 0;
  unsigned block_size = 0;
  std::string fd_code;
  std::string fe_code;
  std::string hash_type;
};

void Usage(const char* nombre_programa) {
  std::cerr << "Uso:\n";
  std::cerr << nombre_programa
            << " -ts <table_size> -fd <mod|sum|rand> -hash <open|close> "
               "[ -bs <block_size> -fe <lineal|cuadratica|doble|redispersion>]\n";
}

Options Parseo(int argc, char* argv[]) {
  Options options;

  for(int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if(arg == "-ts") {
      if(i + 1 >= argc) throw std::invalid_argument("Falta valor para -ts");
      options.table_size = static_cast<unsigned>(std::stoul(argv[++i]));
    } else if(arg == "-fd") {
      if(i + 1 >= argc) throw std::invalid_argument("Falta valor para -fd");
      options.fd_code == argv[++i];
    } else if(arg == "-hash") {
      if(i + 1 >= argc) throw std::invalid_argument("Falta valor para -hash");
      options.hash_type == argv[++i];
    } else if(arg == "-bs") {
      if(i + 1 >= argc) throw std::invalid_argument("Falta valor para -bs");
      options.block_size ==  static_cast<unsigned>(std::stoul(argv[++i]));
    } else if(arg == "-fe") {
      if(i + 1 >= argc) throw std::invalid_argument("Falta valor para -fe");
      options.fe_code == argv[++i];
    } else {
      throw std::invalid_argument("Opción desconocida : " + arg);
    }
  }

  if(options.table_size == 0) {
    throw std::invalid_argument("El tamaño de la tabla debe ser mayor que 0");
  }
  if(options.fd_code.empty()) {
    throw std::invalid_argument("Se debe especificar la función de dispersion");
  }
  if(options.hash_type != "open" && options.hash_type != "close") {
    throw std::invalid_argument("El valor de -hash debe ser open o close");
  }
  if(options.hash_type == "close") {
    if(options.block_size == 0) {
    throw std::invalid_argument("Se debe especificar el tamaño de bloque");
    }
    if(options.fe_code.empty()) {
      throw std::invalid_argument("Se debe especificar la función de exploración");
    }
  }

  return options;
}

std::unique_ptr<DispersionFunction<nif>> CreateDispersion(const std::string& code, unsigned table_size) {
  if(code == "mod") {
    return std::make_unique<ModuloDispersion<nif>>(table_size);
  }

  if(code == "sum") {
    return std::make_unique<SumaDispersion<nif>>(table_size);
  }

  if(code == "rand") {
    return std::make_unique<RandDispersion<nif>>(table_size);
  }
}