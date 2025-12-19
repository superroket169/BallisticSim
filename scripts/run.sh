ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT" || exit 1
export PATH="$ROOT/bin:$PATH"
wine build/main.exe
read -p "Devam etmek için Enter'a bas..."