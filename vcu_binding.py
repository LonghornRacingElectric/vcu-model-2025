# File: vcu_bindings.py
import ctypes
import os
import platform

# --- Basic C Type Aliases ---
_int = ctypes.c_int
_float = ctypes.c_float
_bool = ctypes.c_bool  # Assumes C uses <stdbool.h>

# --- Constants from Headers ---
LOOKUP2D_POINTS_X = 11  # From Lookup2D.h
LOOKUP2D_POINTS_Y = 11  # From Lookup2D.h

# --- Enum Definitions (as constants) ---
# From AppsProcessor.h
APPS_STATUS = {
    "APPS_OK": 0,
    "APPS_DISAGREE": 1,
    "APPS_OUT_OF_RANGE": 2,
}
_APPS_STATUS_enum = _int  # Use c_int for enums in ctypes

# From Stompp.h
STOMPP_OUTPUT = {
    "STOMPP_OK": 0,
    "STOMPP_FAULT": 1,
}
_STOMPP_OUTPUT_enum = _int  # Use c_int for enums in ctypes

# --- C Structure Definitions ---

# Forward declarations for nested structs if needed (not strictly necessary in Python)
# class VcuParameters(ctypes.Structure): pass
# class Timer(ctypes.Structure): pass
# ... etc ...

# --- Util Structs ---


# From util/Lookup1D.h
class Lookup1D(ctypes.Structure):
    _fields_ = [
        ("x0", _float),
        ("x1", _float),
        (
            "xP",
            _float,
        ),  # Assuming this was intended, it's present in VcuParameters.h but not Lookup1D.h
        (
            "yP",
            _float,
        ),  # Assuming this was intended, it's present in VcuParameters.h but not Lookup1D.h
        ("y", _float * 11),  # Array of 11 floats
    ]


# From util/Lookup2D.h
class Lookup2D(ctypes.Structure):
    _fields_ = [
        ("x0", _float),
        ("x1", _float),
        ("y0", _float),
        ("y1", _float),
        ("z", (_float * LOOKUP2D_POINTS_X) * LOOKUP2D_POINTS_Y),  # 2D Array [11][11]
    ]


# From util/PIDController.h
class PIDController(ctypes.Structure):
    _fields_ = [
        ("_kp", _float),
        ("_ki", _float),
        ("_kd", _float),
        ("_setpoint", _float),
        ("_error", _float),
        ("_integral", _float),
        ("_derivative", _float),
        ("_prevError", _float),
        ("_maxOutput", _float),
        ("_minOutput", _float),
        ("_integralLimit", _float),
        ("_derivativeLimit", _float),
        ("_integralResetLimit", _float),
        ("output", _float),
    ]


# From util/LowPassFilter.h
class LowPassFilter(ctypes.Structure):
    _fields_ = [
        ("timeConstant", _float),
        ("accumulator", _float),
    ]


# From util/Timer.h
class Timer(ctypes.Structure):
    _fields_ = [
        ("duration", _float),
        ("time", _float),
    ]


# From util/Debounce.h
class Debounce(ctypes.Structure):
    _fields_ = [
        ("timer", Timer),
        ("state", _bool),
    ]


# --- Block Parameter Structs ---


# From blocks/AppsProcessor.h
class APPSParameters(ctypes.Structure):
    _fields_ = [
        ("sensorInRangeUpperBound", _float),
        ("sensorInRangeLowerBound", _float),
        ("allowedPlausibilityRange", _float),
        ("appsDeadzoneTopPercent", _float),
        ("appsDeadzoneBottomPercent", _float),
        ("appsMaxImplausibilityTime", _float),
        ("pedal1Bias", _float),
    ]


# From blocks/Stompp.h
class STOMPPParameters(ctypes.Structure):
    _fields_ = [
        ("mechanicalBrakeThreshold", _float),
        ("stomppAppsCutoffThreshold", _float),
        ("stomppAppsRecoveryThreshold", _float),
    ]


# From blocks/TorqueMap.h
class TorqueMapParameters(ctypes.Structure):
    _fields_ = [
        ("mapPedalToTorqueRequest", Lookup1D),
    ]


# From blocks/Cooling.h
class CoolingParameters(ctypes.Structure):
    _fields_ = [
        ("motor_fan_on_threshold", _float),
        ("motor_fan_full_speed_threshold", _float),
        ("batt_fan_on_threshold", _float),
        ("batt_fan_full_speed_threshold", _float),
    ]


# From blocks/BrakeLight.h
class BrakeLightParameters(ctypes.Structure):
    _fields_ = [
        ("bseLightOnPercent", _float),
        ("bseTimeConstant", _float),
    ]


# --- Block Input Structs ---


# From blocks/AppsProcessor.h
class APPSInputs(ctypes.Structure):
    _fields_ = [
        ("pedal1Percent", _float),
        ("pedal2Percent", _float),
    ]


# From blocks/Stompp.h
class STOMPPInputs(ctypes.Structure):
    _fields_ = [
        ("apps_percent", _float),
        ("bse_percent", _float),
    ]


# From blocks/TorqueMap.h
class TorqueMapInputs(ctypes.Structure):
    _fields_ = [
        ("apps", _float),
        ("motorTemp", _float),
        ("motorRpm", _float),
        ("inverterTemp", _float),
        ("batteryTemp", _float),
        ("batterySoc", _float),
        ("batteryVoltage", _float),
        ("batteryCurrent", _float),
    ]


# From blocks/Cooling.h
class CoolingInputs(ctypes.Structure):
    _fields_ = [
        ("battRadInTemp", _float),
        ("battRadOutTemp", _float),
        ("motorRadInTemp", _float),
        ("motorRadOutTemp", _float),
        ("motorInverterTemp", _float),
        ("ambientTemp", _float),
        ("battTach", _int),
        ("motorTach", _int),
    ]


# From blocks/BrakeLight.h
class BrakeLightInputs(ctypes.Structure):
    _fields_ = [
        ("bsePercent", _float),
    ]


# --- Block Output Structs ---


# From blocks/AppsProcessor.h
class APPSOutputs(ctypes.Structure):
    _fields_ = [
        ("status", _APPS_STATUS_enum),
        ("pedalPercent", _float),
    ]


# From blocks/Stompp.h
class STOMPPOutputs(ctypes.Structure):
    _fields_ = [
        ("output", _STOMPP_OUTPUT_enum),
    ]


# From blocks/TorqueMap.h
class TorqueMapOutputs(ctypes.Structure):
    _fields_ = [
        ("torqueRequest", _float),
    ]


# From blocks/Cooling.h
class CoolingOutputs(ctypes.Structure):
    _fields_ = [
        ("pump1Output", _float),
        ("pump2Output", _float),
        ("motorFansOutput", _float),
        ("batteryFansOutput", _float),
    ]


# From blocks/BrakeLight.h
class BrakeLightOutputs(ctypes.Structure):
    _fields_ = [
        ("lightOn", _bool),
    ]


# --- Top-Level VCU Structs ---


# From VcuModel.h
class VCUModelInputs(ctypes.Structure):
    _fields_ = [
        ("apps", APPSInputs),
        ("stompp", STOMPPInputs),
        ("torque", TorqueMapInputs),
        ("cooling", CoolingInputs),
        ("brake_light", BrakeLightInputs),
        ("drive_switch_enabled", _bool),  # Assuming drive_switch is digital input
    ]


# From VcuModel.h
class VCUModelOutputs(ctypes.Structure):
    _fields_ = [
        ("apps", APPSOutputs),
        ("stompp", STOMPPOutputs),
        ("torque", TorqueMapOutputs),
        ("cooling", CoolingOutputs),
        ("brake_light", BrakeLightOutputs),
    ]


# From VcuModel.h
class VCUModelParameters(ctypes.Structure):
    _fields_ = [
        ("apps", APPSParameters),
        ("stompp", STOMPPParameters),
        ("torque", TorqueMapParameters),
        ("cooling", CoolingParameters),
        ("brake_light", BrakeLightParameters),
        # Add other parameters if they exist at this top level
    ]


# --- Library Loading ---

# !!! IMPORTANT: Update this path to your compiled shared library !!!
_LIB_FILENAME = ""
if platform.system() == "Windows":
    # Example: "build/src/Debug/vcu_model_shared.dll" or "build_shared/vcu_model_shared.dll"
    _LIB_FILENAME = "vcu_model_shared.dll"
elif platform.system() == "Darwin":  # macOS
    # Example: "build/src/libvcu_model_shared.dylib" or "build_shared/libvcu_model_shared.dylib"
    _LIB_FILENAME = "libvcu_model_shared.dylib"
else:  # Linux and others
    # Example: "build/src/libvcu_model_shared.so" or "build_shared/libvcu_model_shared.so"
    _LIB_FILENAME = "libvcu_model_shared.so"

# Construct the path relative to this script file
_SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))
# --- !! MODIFY THIS RELATIVE PATH !! ---
_RELATIVE_LIB_PATH = os.path.join("build", _LIB_FILENAME)  # Example path
# _RELATIVE_LIB_PATH = os.path.join('..', 'build', 'src', _LIB_FILENAME) # Another Example
# --- !! MODIFY THIS RELATIVE PATH !! ---

_LIB_PATH = os.path.abspath(os.path.join(_SCRIPT_DIR, _RELATIVE_LIB_PATH))

# Load the library
try:
    if not os.path.exists(_LIB_PATH):
        raise FileNotFoundError(
            f"Shared library not found at: {_LIB_PATH}\n"
            "Please build the C code as a shared library and "
            "update the _LIB_PATH variable in this script."
        )
    _lib = ctypes.CDLL(_LIB_PATH)
    print(f"Successfully loaded library: {_LIB_PATH}")
except (OSError, FileNotFoundError) as e:
    print(f"Error loading shared library: {e}")
    _lib = None
    exit(1)  # Exit if library loading fails

# --- Function Prototypes ---
if _lib:
    try:
        # void VCUModel_evaluate(VCUModelInputs *inputs, VCUModelOutputs *outputs, float deltaTime);
        _lib.VCUModel_evaluate.argtypes = [
            ctypes.POINTER(VCUModelInputs),
            ctypes.POINTER(VCUModelOutputs),
            _float,
        ]
        _lib.VCUModel_evaluate.restype = None  # void

        # void VCUModel_set_parameters(VCUModelParameters *parameters);
        _lib.VCUModel_set_parameters.argtypes = [ctypes.POINTER(VCUModelParameters)]
        _lib.VCUModel_set_parameters.restype = None  # void

        # --- Add prototypes for other exported functions if needed ---
        # e.g., _lib.Lookup1D_evaluate.argtypes = [ctypes.POINTER(Lookup1D), _float]
        #       _lib.Lookup1D_evaluate.restype = _float

    except AttributeError as e:
        print(f"Error setting up function prototype: {e}")
        print("Check function names match exported symbols in the shared library.")
        print(
            "Possible issues: Library not built correctly, C++ name mangling, or function not exported."
        )
        _lib = None  # Prevent further use
        exit(1)
else:
    print("Library not loaded, cannot set function prototypes.")


# --- Helper Function to access library (optional) ---
def get_lib():
    """Returns the loaded ctypes library object."""
    if not _lib:
        raise RuntimeError("VCU library was not loaded successfully.")
    return _lib


# --- Example Usage ---
if __name__ == "__main__":
    if not _lib:
        print("\nLibrary not loaded. Cannot run example.")
    else:
        print("\n--- Running VCU Model Example ---")

        # 1. Create structure instances
        vcu_params = VCUModelParameters()
        vcu_inputs = VCUModelInputs()
        vcu_outputs = VCUModelOutputs()

        # 2. Populate Parameters (replace with your actual parameter values)
        print("Populating parameters (using placeholder values)...")
        # APPS Parameters
        vcu_params.apps.sensorInRangeUpperBound = 1.0
        vcu_params.apps.sensorInRangeLowerBound = 0.0
        vcu_params.apps.allowedPlausibilityRange = 0.10
        vcu_params.apps.appsDeadzoneTopPercent = 0.90
        vcu_params.apps.appsDeadzoneBottomPercent = 0.10
        vcu_params.apps.appsMaxImplausibilityTime = 0.100
        vcu_params.apps.pedal1Bias = 0.5  # Example bias

        # STOMPP Parameters
        vcu_params.stompp.mechanicalBrakeThreshold = 0.10
        vcu_params.stompp.stomppAppsCutoffThreshold = 0.25
        vcu_params.stompp.stomppAppsRecoveryThreshold = 0.05

        # TorqueMap Parameters
        # Example: Linear map from 0-1 pedal -> 0-200 Nm torque
        vcu_params.torque.mapPedalToTorqueRequest.x0 = 0.0
        vcu_params.torque.mapPedalToTorqueRequest.x1 = 1.0
        vcu_params.torque.mapPedalToTorqueRequest.xP = 1.0
        vcu_params.torque.mapPedalToTorqueRequest.yP = 230.0
        # Populate the 'y' array for the lookup table
        for i in range(11):
            vcu_params.torque.mapPedalToTorqueRequest.y[i] = (
                i / 10.0
            ) * 200.0  # Linear example

        # Cooling Parameters
        vcu_params.cooling.motor_fan_on_threshold = 40.0
        vcu_params.cooling.motor_fan_full_speed_threshold = 60.0
        vcu_params.cooling.batt_fan_on_threshold = 35.0
        vcu_params.cooling.batt_fan_full_speed_threshold = 50.0

        # BrakeLight Parameters
        vcu_params.brake_light.bseLightOnPercent = 0.05
        vcu_params.brake_light.bseTimeConstant = 0.05  # Example time constant

        # 3. Set Parameters in the C model
        try:
            print("Calling VCUModel_set_parameters...")
            _lib.VCUModel_set_parameters(ctypes.byref(vcu_params))
            print("Parameters set.")
        except Exception as e:
            print(f"Error calling VCUModel_set_parameters: {e}")
            exit(1)

        # 4. Simulate multiple steps
        deltaTime = 0.01  # Example delta time (10ms)
        num_steps = 5

        print(f"\nSimulating {num_steps} steps with dt={deltaTime}s...")

        for step in range(num_steps):
            # Populate Inputs for this step (replace with actual test inputs)
            # APPS Inputs
            pedal_sim = (
                (step / (num_steps - 1)) if num_steps > 1 else 0.5
            )  # Simulate pedal press 0 -> 1
            vcu_inputs.apps.pedal1Percent = pedal_sim
            vcu_inputs.apps.pedal2Percent = pedal_sim  # Assume sensors agree for now

            # STOMPP Inputs
            vcu_inputs.stompp.apps_percent = pedal_sim
            vcu_inputs.stompp.bse_percent = 0.0  # Assume no braking

            # TorqueMap Inputs
            vcu_inputs.torque.apps = pedal_sim
            vcu_inputs.torque.motorTemp = 45.0
            vcu_inputs.torque.motorRpm = 1000.0 + step * 500
            vcu_inputs.torque.inverterTemp = 40.0
            vcu_inputs.torque.batteryTemp = 30.0
            vcu_inputs.torque.batterySoc = 0.8  # 80%
            vcu_inputs.torque.batteryVoltage = 400.0
            vcu_inputs.torque.batteryCurrent = 10.0 * pedal_sim

            # Cooling Inputs
            vcu_inputs.cooling.battRadInTemp = 31.0
            vcu_inputs.cooling.battRadOutTemp = 30.0
            vcu_inputs.cooling.motorRadInTemp = 46.0
            vcu_inputs.cooling.motorRadOutTemp = 45.0
            vcu_inputs.cooling.motorInverterTemp = 40.0
            vcu_inputs.cooling.ambientTemp = 25.0
            vcu_inputs.cooling.battTach = 2000
            vcu_inputs.cooling.motorTach = 3000

            # BrakeLight Inputs
            vcu_inputs.brake_light.bsePercent = 0.0  # No braking

            # Other Top-Level Inputs
            vcu_inputs.drive_switch_enabled = True

            # Call the evaluation function
            try:
                _lib.VCUModel_evaluate(
                    ctypes.byref(vcu_inputs), ctypes.byref(vcu_outputs), deltaTime
                )
            except Exception as e:
                print(f"Error calling VCUModel_evaluate on step {step}: {e}")
                break  # Stop simulation on error

            # Read Outputs (Access fields from vcu_outputs)
            print(f"\n--- Step {step} Outputs ---")
            print(
                f"  APPS Status: {vcu_outputs.apps.status} (0=OK, 1=Disagree, 2=OutRange)"
            )
            print(f"  APPS Pedal %: {vcu_outputs.apps.pedalPercent:.3f}")
            print(f"  STOMPP Status: {vcu_outputs.stompp.output} (0=OK, 1=Fault)")
            print(f"  Torque Request (Nm): {vcu_outputs.torque.torqueRequest:.2f}")
            print(f"  Cooling Motor Fans: {vcu_outputs.cooling.motorFansOutput:.2f}")
            print(
                f"  Cooling Battery Fans: {vcu_outputs.cooling.batteryFansOutput:.2f}"
            )
            print(f"  Cooling Pump 1: {vcu_outputs.cooling.pump1Output:.2f}")
            print(f"  Cooling Pump 2: {vcu_outputs.cooling.pump2Output:.2f}")
            print(f"  Brake Light On: {vcu_outputs.brake_light.lightOn}")

        print("\nSimulation finished.")
