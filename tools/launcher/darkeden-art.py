# SPDX-License-Identifier: GPL-3.0-or-later
"""Generate the DarkEden logo and backgrounds for the staged PS5 package."""
import sys
from pathlib import Path

from PIL import Image, ImageDraw, ImageFilter

LEAF = [[50,5],[59,25],[66,20],[64,43],[78,32],[81,42],[95,39],[89,54],[95,61],[66,77],[69,84],[54,82],[54,96],[46,96],[46,82],[31,84],[34,77],[5,61],[11,54],[5,39],[19,42],[22,32],[36,43],[34,20],[41,25]]

def maple(draw, x, y, size):
    draw.polygon([(x + px * size / 100, y + py * size / 100) for px, py in LEAF],
                 fill="#81d9ff")

def backdrop(width, height):
    image = Image.new("RGB", (width, height))
    draw = ImageDraw.Draw(image)
    for y in range(height):
        fraction = y / height
        draw.line((0, y, width, y), fill=(7, 16 + int(20 * fraction), 35 + int(35 * fraction)))
    for x in range(-height, width, width // 12):
        draw.line((x, height, x + height, 0), fill="#102848", width=max(1, width // 850))
    return image

def main(app):
    art = app / "ui/art"
    system = app / "sce_sys"
    brand = Image.new("RGBA", (512, 512), "#071123")
    draw = ImageDraw.Draw(brand)
    draw.rounded_rectangle((12, 12, 500, 500), radius=108, fill="#0b1d39", outline="#386b9d", width=8)
    maple(draw, 64, 54, 384)
    brand.save(art / "brand.tga", orientation=1)
    brand.convert("RGB").save(system / "icon0.png")
    background = backdrop(2048, 1152)
    background.convert("RGBA").save(art / "backdrop.tga", orientation=1)
    blurred = background.resize((256, 144)).filter(ImageFilter.GaussianBlur(6))
    blurred.convert("RGBA").save(art / "backdrop-blur.tga", orientation=1)
    splash = backdrop(3840, 2160)
    maple(ImageDraw.Draw(splash), 1510, 625, 820)
    for name in ("pic0.dds", "pic1.dds"):
        splash.convert("RGBA").save(system / name, format="DDS")
    for catalog in (app / "ui/lang").glob("*.po"):
        original = catalog.read_text(encoding="utf-8")
        catalog.write_text(original.replace("ProsperoEden", "DarkEden"), encoding="utf-8")

if __name__ == "__main__":
    main(Path(sys.argv[1]))
