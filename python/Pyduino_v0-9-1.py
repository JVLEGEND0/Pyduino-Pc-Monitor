import psutil, time, requests, serial, sys, spotipy
from spotipy.oauth2 import SpotifyOAuth

time.sleep(5)

'''
--------- ALERT !!!!!!!! -----------
Before running the code, make sure to edit the credentials below and line 39.
'''

#ARDUINO INFO:
COM = "YOUR_COM_PORT" #PORT WHERE YOUR ARDUINO IS CONNECTED
#SPOTFY INFO:
CLIENT_ID = "YOUR_CLIENT_ID"
CLIENT_SECRET = "YOUR CLIENT_SECRET"
REDIRECT_URI = "YOUR REDIRECT_URI" #like "https://127.0.0.1:8080/callback"
#LIBRE HARDWARE MONITOR INFO:
PORT_LHM = "YOUR PORT OF REMOTE WEB SERVER"

sp = spotipy.Spotify(auth_manager=SpotifyOAuth(
    client_id=CLIENT_ID,
    client_secret=CLIENT_SECRET,
    redirect_uri=REDIRECT_URI, 
    scope="user-read-playback-state"
))

#print(sp.current_playback())

try:
    ser = serial.Serial(COM, 9600)
except serial.SerialException:
    #print("Error: Could not open serial port COM. Please check the connection.")
    sys.exit(0)


def get_cpu_temp():
    url = f'http://localhost:{PORT_LHM}/data.json'
    info = requests.get(url).json()
    sensor_path = '/intelcpu/0/temperature/6' #It may vary from PC to PC; this one was tested on an Intel processor.

    def find_sensor(node):
        if isinstance(node, dict):
            if node.get('SensorId') == sensor_path:
                return node
            for child in node.get('Children', []):
                result = find_sensor(child)
                if result:
                    return result
        elif isinstance(node, list):
            for item in node:
                result = find_sensor(item)
                if result:
                    return result
        return None

    sensor = find_sensor(info)
    return sensor.get('Value') if sensor else None

def get_system_info():
    cpu_usage = float(psutil.cpu_percent())

    try:
        cpu_temp_raw = get_cpu_temp() 
        cpu_temp = cpu_temp_raw.replace('°C', '')
        cpu_temp = cpu_temp.replace(',', '.')
        cpu_temp = float(cpu_temp)
    except:
        cpu_temp = -1.0    
    
    cpu_alert = int(cpu_temp > 80.0)    

    memory_usage = float(psutil.virtual_memory().percent)
    memory_total = float(psutil.virtual_memory().total / (1024 * 1024 * 1024))
    memory_used = float(psutil.virtual_memory().used / (1024 * 1024 * 1024))
    
    disk_usage = psutil.disk_usage('C:/').percent
    disk_total = float(psutil.disk_usage('C:/').total / (1024 * 1024 * 1024))
    disk_used = float(psutil.disk_usage('C:/').used / (1024 * 1024 * 1024))

    return cpu_usage, cpu_temp, memory_usage, cpu_alert, memory_total, memory_used, disk_usage, disk_total, disk_used

try:
    while True:
        cpu, temp_cpu, memory, cpu_high_temp, memory_t, memory_u, disk, disk_t, disk_u = get_system_info()

        playback = sp.current_playback()

        if playback and playback["item"]:
            musica = playback["item"]["name"]
            musica = musica.replace(",", " ")
            tempo_sec = int(playback["progress_ms"]) // 1000
            tempo_min = tempo_sec // 60
            tempo_sec = tempo_sec % 60
            duracao_sec = int(playback["item"]["duration_ms"]) // 1000
            duracao_min = duracao_sec // 60
            duracao_sec = duracao_sec % 60
        else:
            musica = "No music playing"
            tempo_min = 0
            tempo_sec = 0
            duracao_min = 0
            duracao_sec = 0

        data = f"{cpu},{temp_cpu},{memory},{cpu_high_temp},{memory_t},{memory_u},{disk},{disk_t},{disk_u},{musica},{tempo_min},{tempo_sec:02},{duracao_min},{duracao_sec:02}\n"
        ser.write(data.encode())
        #print(f"CPU Usage: {cpu}% | CPU Temp: {temp_cpu} °C\n RAM Usage: {memory}% | RAM Used: {memory_u:.2f}GB/{memory_t:.2f}GB")
        time.sleep(0.8)
        #os.system('cls' if os.name == 'nt' else 'clear')
except serial.SerialException:
    sys.exit(0)        
