INITED = False

def init():
    global INITED
    
    if INITED:
        return
    INITED = True

    print("Initializing...")
