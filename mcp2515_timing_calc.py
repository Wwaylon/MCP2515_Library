import math
# calculate BRP, T_ps1 and T_ps2 for the MCP2515

def TQ(brp, Fosc):
        return float(2*brp)/Fosc

def TQBit(fbaud, tq):
        return 1/(float(fbaud*tq))

# ------

# Constants

Fosc = 8000000        # 8 MHz
Tosc = 1/float(Fosc)

Fbaud = [ 50000, 100000, 125000, 250000, 500000, 1000000 ] # kHz bit rate

baudrate = 125000 # kHz

# bit time sections in quantities of time quantas (TQ)
t_syncseg   = 1    # fixed
t_propseg   = 1    # fixed, min=1 max=8
t_ps1       = 1    # min=1 max=8
t_ps2       = 2    # min=2 max=8
SJW         = 1    # fixed

SamplePoint = .65   # percent

# -----

print ("MCP2515 Settings:")
print ("BTLMODE = 1")

for brp in range(1, 50):
        for b in Fbaud:
                tqall = TQBit(b, TQ(brp, 8000000))
                tq70 = math.floor(tqall * SamplePoint)
                t_ps1 = tq70 - ( t_syncseg + t_propseg )
                t_ps2 = tqall - t_ps1  - t_syncseg - t_propseg

                if (t_ps1 < 1 or t_ps1 > 8 or t_ps2 < 2):
                        continue

                if ((t_propseg + t_ps1) < t_ps2):
                        continue
                if (t_ps2 <= SJW):
                        continue
                cnf1 = 0x00 | (brp-1)
                cnf2 = 0xc0 | ((int(t_ps1)-1)<<3) | (int(t_propseg)-1)
                cnf3 = 0x80 | (int(t_ps2)-1)

                print ("Fbaud = %dkHz; tqall = %d; tq70 = %d; BRP = %d; t_ps1 = %d; t_ps2 = %d; cnf1=%x; cnf2=%x; cnf3 =%x" % (b/1000, tqall, tq70, brp, t_ps1, t_ps2, cnf1, cnf2, cnf3))
                