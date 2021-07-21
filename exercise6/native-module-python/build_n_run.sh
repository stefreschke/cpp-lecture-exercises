# have python3 available on path (no other requirements)
python3 -m venv venv
source venv/bin/activate
pip install cffi
echo "=============="
echo "running program"
echo "=============="
python3 main.py
