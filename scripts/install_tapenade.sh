#!/usr/bin/env bash

JAVA_VERSION="${JAVA_VERSION:-17}"
TAPENADE_VERSION="${TAPENADE_VERSION:-3.16}"
PREFIX="${INSTALL_DIR:-/${HOME}/tapenade}"

log() { echo "==> $*"; }

usage(){
  cat <<EOF
Usage: $0 [--java-version N] [--tapenade-version V] [--install-dir DIR]

Environment variables accepted: JAVA_VERSION, TAPENADE_VERSION, INSTALL_DIR, TAPENADE_URL
Options:
  --java-version N       Specify Java version to install (default: ${JAVA_VERSION})
  --tapenade-version V   Specify Tapenade version to install (default: ${TAPENADE_VERSION})
  --install-dir DIR      Specify installation directory (default: ${PREFIX})
EOF
}

install_java_mac(){
  if ! command -v brew >/dev/null 2>&1; then
    log "Homebrew not found. Installing Homebrew..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
  fi
  log "Installing Java ${JAVA_VERSION} via Homebrew..."
  if brew info "openjdk@${JAVA_VERSION}" >/dev/null 2>&1; then
    brew install "openjdk@${JAVA_VERSION}"
  else
    brew install openjdk
  fi
  log "Java installation (Mac) completed. You may need to add OpenJDK to PATH if necessary."
}

install_java_linux(){
   mkdir -p "$PREFIX"
   wget https://javadl.oracle.com/webapps/download/AutoDL?BundleId=253185_f7fe8e644f724108bdb54139381e29a7 -O ${PREFIX}/jre.tar.gz
   tar xzf ${PREFIX}/jre.tar.gz
}

install_tapenade(){
  mkdir -p "$PREFIX"
  TMPDIR=$(mktemp -d)
  trap 'rm -rf "$TMPDIR"' EXIT

  TAPENADE_URL="${TAPENADE_URL:-https://tapenade.gitlabpages.inria.fr/tapenade/distrib/tapenade_${TAPENADE_VERSION}.tar}"
  log "Downloading Tapenade from ${TAPENADE_URL}"
  curl -L --fail -o "$TMPDIR/tapenade.tar" "$TAPENADE_URL"
  log "Extracting to ${PREFIX}"
  tar -xf "$TMPDIR/tapenade.tar" -C "$PREFIX"
  log "Tapenade installed into ${PREFIX} (verify contents)."
}

parse_args(){
  while [[ $# -gt 0 ]]; do
    case "$1" in
      --java-version)
        if [[ -z ${2:-} || "$2" == --* ]]; then
          echo "Error: --java-version requires a value" >&2
          usage
          exit 1
        fi
        JAVA_VERSION="$2"
        shift 2
        ;;
      --tapenade-version)
        if [[ -z ${2:-} || "$2" == --* ]]; then
          echo "Error: --tapenade-version requires a value" >&2
          usage
          exit 1
        fi
        TAPENADE_VERSION="$2"
        shift 2
        ;;
      --install-dir)
        if [[ -z ${2:-} || "$2" == --* ]]; then
          echo "Error: --install-dir requires a value" >&2
          usage
          exit 1
        fi
        PREFIX="$2"
        shift 2
        ;;
      --help|-h)
        usage
        exit 0
        ;;
      *)
        echo "Unknown option: $1" >&2
        usage
        exit 1
        ;;
    esac
  done
}

main(){
  parse_args "$@"

  if ! command -v java >/dev/null 2>&1; then
    OS=$(uname -s)
    case "$OS" in
      Darwin)
        log "Detected MacOS"
        install_java_mac
        ;;
      Linux)
        log "Detected Linux"
        install_java_linux
        ;;
      *)
        echo "Unsupported OS: $OS" >&2
        exit 1
        ;;
    esac
 fi

  install_tapenade

  TAPENADE_BIN="${PREFIX}/tapenade_${TAPENADE_VERSION}/bin"
  export PATH="${TAPENADE_BIN}:${PREFIX}/jre1.8.0_491/bin:${PATH}"
  alias tapenade="${TAPENADE_BIN}/tapenade"
  tapenade -version

  log "Added ${TAPENADE_BIN} to PATH"
  log "Created alias: tapenade -> ${TAPENADE_BIN}/tapenade"
  log "Done."
}

main "$@"
