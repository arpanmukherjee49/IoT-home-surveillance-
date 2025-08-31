# server.py - Flask server for webcam snapshot + audio alert
from flask import Flask, jsonify, send_from_directory
import cv2, time, os, threading, platform

OUT_DIR = "captures"
CAM_INDEX = 0
ALERT_AUDIO = "alert.mp3"

os.makedirs(OUT_DIR, exist_ok=True)

try:
    from playsound import playsound
    HAVE_PLAYSOUND = True
except Exception:
    HAVE_PLAYSOUND = False

app = Flask(__name__)
cap = cv2.VideoCapture(CAM_INDEX)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

def play_alert():
    if not os.path.exists(ALERT_AUDIO):
        print("Alert audio not found:", ALERT_AUDIO)
        return
    if HAVE_PLAYSOUND:
        try:
            playsound(ALERT_AUDIO)
            return
        except Exception as e:
            print("playsound failed:", e)
    sys_platform = platform.system()
    try:
        if sys_platform == "Windows":
            os.startfile(ALERT_AUDIO)
        elif sys_platform == "Darwin":
            os.system(f"afplay \"{ALERT_AUDIO}\" &")
        else:
            os.system(f"mpg123 \"{ALERT_AUDIO}\" >/dev/null 2>&1 &")
    except Exception as e:
        print("Fallback audio play failed:", e)

@app.route('/capture')
def capture():
    ret, frame = cap.read()
    if not ret:
        return jsonify({'status':'error','msg':'camera read failed'}), 500
    fname = f"capture_{int(time.time())}.jpg"
    path = os.path.join(OUT_DIR, fname)
    cv2.imwrite(path, frame)
    print("Saved:", path)
    threading.Thread(target=play_alert, daemon=True).start()
    return jsonify({'status':'ok','file':fname})

@app.route('/captures/<path:filename>')
def serve_file(filename):
    return send_from_directory(OUT_DIR, filename)

if __name__ == "__main__":
    print("Starting server on http://0.0.0.0:5000")
    app.run(host='0.0.0.0', port=5000)
