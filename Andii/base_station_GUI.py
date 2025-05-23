import serial
from time import sleep
import arcade
from arcade.color import AIR_SUPERIORITY_BLUE
from math import sin, cos

WINDOW_WIDTH = 1300 #1526
WINDOW_HEIGHT = 650 #763
SCREEN_TITLE = "Boat Base GUI"

scale_gps_1 = [53.9469781, -1.0284061] # latitude, longitude
scale_gps_2 = [53.9453251, -1.0284061]

scale_position_1 = [470, 443] # x, y, opposite of the longitude/latitude
scale_position_2 = [470, 95]
# Assuming linear change on human scale, 31 pixels per 0.0001 degrees
# Assuming almost spherical Earth, 111260.66m per 1 degree, or 11.126066m per 31 pixels

points_of_interest = []
boat_data = [] 
package_size = 7

def pixels_to_degrees(x, y):
    dx = x - scale_position_1[0]
    dy = y - scale_position_1[1]
    dx_degrees = dx/310000
    dy_degrees = dy/310000
    latitude = round(dy_degrees+scale_gps_1[0], 7)
    longitude = round(dx_degrees+scale_gps_1[1], 7)
    return latitude, longitude

def degrees_to_pixels(latitude, longitude):
    dx_degrees = longitude - scale_gps_1[1]
    dy_degrees = latitude - scale_gps_1[0]
    dx = dx_degrees*310000
    dy = dy_degrees*310000
    x = dx + scale_position_1[0]
    y = dy + scale_position_1[1]
    return x, y

def boat_signal():
    global boat_data
    # Boat Data: [package_number, longitude, latitude, rotation, winch_status, temperature, Ph]
    """boat_data = list(str(port.readline())[2:][:-5].split())
    if len(boat_data) == package_size:
        for i in range(len(boat_data)):
            boat_data[i] = float(boat_data[i])
        boat_data[1] = boat_data[1]/10000000
        boat_data[2] = boat_data[2]/10000000"""
    boat_data = [17, 53.9466222, -1.0281674, 105.0, 0, 17.6, 7.1] # fake values for testing without the need of an arduino
    sleep(0.1)


class MyGame(arcade.Window):
    def __init__(self):
        super().__init__(WINDOW_WIDTH, WINDOW_HEIGHT, SCREEN_TITLE, resizable=True)
        self.background = arcade.load_texture("lake.png")  # Use your image path here

    def on_update(self, delta_time):
        boat_signal()

    def on_draw(self):
        arcade.draw_texture_rect(
            self.background,
            arcade.LBWH(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT),
        )

        arcade.draw_lbwh_rectangle_filled(0, 250, 300, 400, arcade.color.WHITE)
        arcade.draw_circle_filled(scale_position_1[0], scale_position_1[1], 3, arcade.color.AIR_SUPERIORITY_BLUE)
        arcade.draw_circle_filled(scale_position_2[0], scale_position_2[1], 3, arcade.color.AIR_SUPERIORITY_BLUE)
        arcade.draw_text(f"{scale_gps_1[0]}, {scale_gps_1[1]}", scale_position_1[0], scale_position_1[1],
                         color=AIR_SUPERIORITY_BLUE, font_size=14, bold=True)
        arcade.draw_text(f"{scale_gps_2[0]}, {scale_gps_2[1]}", scale_position_2[0], scale_position_2[1],
                         color=AIR_SUPERIORITY_BLUE, font_size=14, bold=True)

        for num, point in enumerate(points_of_interest):
            arcade.draw_circle_filled(point[0], point[1], 10, [114, 160, 193])
            arcade.draw_circle_filled(point[0], point[1], 28, [114, 160, 193, 64])
            arcade.draw_text(f"{point[2]}, {point[3]}", point[0], point[1],
                             color=AIR_SUPERIORITY_BLUE, font_size=14, bold=True)
            if len(points_of_interest) > 1 and num<len(points_of_interest)-1:
                arcade.draw_line(point[0], point[1], points_of_interest[num+1][0], points_of_interest[num+1][1],
                                 color=AIR_SUPERIORITY_BLUE, line_width=5)

        if len(boat_data) == package_size:
            boat_x, boat_y = degrees_to_pixels(boat_data[1], boat_data[2])
            arcade.draw_circle_filled(boat_x, boat_y, 5, arcade.color.YELLOW_ROSE)
            arcade.draw_line(boat_x, boat_y, boat_x+sin(boat_data[3]*3.14/180)*10, boat_y+cos(boat_data[3]*3.14/180)*10,
                             arcade.color.YELLOW_ROSE, line_width=5)

            arcade.draw_text(f"Longitude:", 20, 615, color=AIR_SUPERIORITY_BLUE, font_size=14, bold=True)
            arcade.draw_text(f"{boat_data[1]}", 155, 615, color=AIR_SUPERIORITY_BLUE, font_size=14, bold=True)

            arcade.draw_text(f"Latitude:", 20, 600, color=AIR_SUPERIORITY_BLUE, font_size=14, bold=True)
            arcade.draw_text(f" {boat_data[2]}", 150, 600, color=AIR_SUPERIORITY_BLUE, font_size=14, bold=True)

            arcade.draw_text(f"Rotation:", 20, 585, color=AIR_SUPERIORITY_BLUE, font_size=14, bold=True)
            arcade.draw_text(f" {boat_data[3]}", 150, 585, color=AIR_SUPERIORITY_BLUE, font_size=14, bold=True)

            arcade.draw_text(f"Winch Status:", 20, 560, color=AIR_SUPERIORITY_BLUE, font_size=14, bold=True)
            arcade.draw_text(f" {boat_data[4]}", 150, 560, color=AIR_SUPERIORITY_BLUE, font_size=14, bold=True)

            arcade.draw_text(f"Temperature:", 20, 545, color=AIR_SUPERIORITY_BLUE, font_size=14, bold=True)
            arcade.draw_text(f" {boat_data[5]}", 150, 545, color=AIR_SUPERIORITY_BLUE, font_size=14, bold=True)

            arcade.draw_text(f"Ph:", 20, 530, color=AIR_SUPERIORITY_BLUE, font_size=14, bold=True)
            arcade.draw_text(f" {boat_data[6]}", 150, 530, color=AIR_SUPERIORITY_BLUE, font_size=14, bold=True)

    def on_mouse_press(self, x: int, y: int, button: int, modifiers: int):
        global points_of_interest
        if button != 1:
            points_of_interest = []
        else:
            deg_1, deg_2 = pixels_to_degrees(x, y)
            points_of_interest.append([x, y, deg_1, deg_2])


if __name__ == "__main__":
    global port
    #try:
    #    port = serial.Serial("COM7", baudrate=9600)
    #except:
    #    print("Failed to open serial port")
    #    exit()
    game = MyGame()
    arcade.run()
    arcade.start_render()
