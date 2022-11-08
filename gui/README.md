# PoliTOcean GUI

The GUI is a remake in Python of the project [Monterey](https://github.com/rovsuite/monterey)

## Setting up the environment

1. Create a new virtual environment running
    ```bash
    python3 -m venv env
    ```

2. Activate the virtual environment systems via
      ```bash
      source ./env/bin/activate
      ```
    It can beand deactivated typing `deactivate`.

    On Windows system there is a dedicated script as well to enable and disable the environment in `./env/bin`.


3. Install all the required dependencies using PiP run

    ```bash
    ./env/bin/python3 -m pip install -r requirements.txt
    ```

We do recomend to **locally** ignore such folder adding in `.git/info/exclude` the following line
```
**/env
```

Your environment is set up.

## Run the code

```bash
python3 main.py
```