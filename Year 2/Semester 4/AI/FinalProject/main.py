from bs4 import BeautifulSoup
from kivy.lang import Builder
from kivymd.app import MDApp
from kivy.clock import Clock
from kivymd.uix.boxlayout import MDBoxLayout
from kivymd.uix.button import MDRaisedButton
from kivymd.uix.expansionpanel import MDExpansionPanelOneLine, MDExpansionPanel
from kivymd.uix.label import MDLabel
from kivy.uix.filechooser import FileChooserListView
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.popup import Popup
from kivy.uix.screenmanager import ScreenManager, Screen
from tensorflow.keras.models import load_model
from tensorflow.keras.preprocessing.image import img_to_array, load_img
import numpy as np
import webbrowser
import pickle

from kivy.core.window import Window
import os
class MainLayout(MDBoxLayout):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.parentApp = None

    def open_html_in_browser(self):
        webbrowser.open("file://" + os.path.abspath("produse/recomandari_produse.html"))

    def open_filechooser(self):
        self.filechooser = FileChooserListView()
        buttons = BoxLayout(size_hint_y=None, height="40dp", spacing="10dp", padding="10dp")
        confirm_button = MDRaisedButton(text="Confirmă", on_release=self.confirm_image)
        cancel_button = MDRaisedButton(text="Anulează", on_release=lambda x: self.popup.dismiss())
        buttons.add_widget(confirm_button)
        buttons.add_widget(cancel_button)

        layout = BoxLayout(orientation="vertical")
        layout.add_widget(self.filechooser)
        layout.add_widget(buttons)

        self.popup = Popup(title="Selectează o imagine", content=layout, size_hint=(0.9, 0.9))
        self.popup.open()

    def confirm_image(self, *args):
        if self.filechooser.selection:
            path = self.filechooser.selection[0].replace('\\', '/')
            print("Imagine selectată:", path)
            self.ids.image_preview.source = path
        self.popup.dismiss()

    def convert_html_to_kivy_markup(self, html_text):
        soup = BeautifulSoup(html_text, "html.parser")
        for tag in soup.find_all(["h1", "h2", "h3", "summary"]):
            tag.insert_before(f"\n[b]{tag.get_text(strip=True)}[/b]\n")
            tag.decompose()

        for details in soup.find_all("details"):
            details.unwrap()

        result_lines = []
        from bs4.element import Tag

        def render_node(node, level=0):
            indent = "    " * level

            if isinstance(node, str):
                text = node.strip()
                if text:
                    result_lines.append(f"{indent}{text}")

            elif isinstance(node, Tag):
                if node.name == "li":
                    content_parts = []

                    already_inserted = set()

                    for c in node.descendants:
                        if isinstance(c, Tag) and c.name == "a":
                            href = c.get("href", "#")
                            link_text = c.get_text(strip=True)
                            markup_link = f"[ref={href}][color=ff4081]{link_text}[/color][/ref]"
                            content_parts.append(markup_link)
                            already_inserted.add(link_text)
                        elif isinstance(c, str):
                            text = c.strip()
                            if text and text not in already_inserted:
                                content_parts.append(text)

                    text = " ".join(content_parts).strip()
                    result_lines.append(f"{indent}• {text}")
                    for sublist in node.find_all(["ul", "ol"], recursive=False):
                        for sub_li in sublist.find_all("li", recursive=False):
                            render_node(sub_li, level + 1)

                elif node.name in ["ul", "ol"]:
                    for li in node.find_all("li", recursive=False):
                        render_node(li, level)

                else:
                    for child in node.children:
                        render_node(child, level)

        render_node(soup)

        final_text = "\n".join(result_lines).strip()
        return final_text if final_text else soup.get_text(separator="\n", strip=True)

    def show_recommendations(self):
        image_path = self.ids.image_preview.source
        if not image_path:
            return

        img = load_img(image_path, target_size=(224, 224))
        img_array = img_to_array(img) / 255.0
        img_array = np.expand_dims(img_array, axis=0)
        prediction = self.parentApp.model.predict(img_array)
        class_index = np.argmax(prediction)
        class_name = self.parentApp.label_encoder.inverse_transform([class_index])[0]

        print("Problemă detectată:", class_name)

        soup = BeautifulSoup(self.parentApp.raw_html, "html.parser")

        rutina = soup.find("details")
        rutina_text = self.convert_html_to_kivy_markup(rutina.decode_contents())

        local_section = None
        for li in soup.select("details summary ~ ol > li"):
            if class_name.lower() in li.get_text(strip=True).lower():
                local_section = li
                break

        if local_section:
            parent_li = local_section.find_parent("li")
            if parent_li:
                local_html = self.convert_html_to_kivy_markup(parent_li.decode_contents())
            else:
                local_html = self.convert_html_to_kivy_markup(local_section.decode_contents())
        else:
            local_html = "[i]Nu s-au găsit produse locale pentru această problemă.[/i]"

        screen = self.parentApp.root.get_screen("recomandation")
        screen.ids.detected_problem.text = f"Problemă detectată: {class_name.capitalize()}"

        content_box = screen.ids.recommendation_content_box
        content_box.clear_widgets()

        content_box.add_widget(MDExpansionPanel(
            icon="spa",
            content=RoutineBox(text=rutina_text),
            panel_cls=MDExpansionPanelOneLine(text="Rutina completă ️")
        ))

        content_box.add_widget(MDExpansionPanel(
            icon="flask",
            content=RoutineBox(text=local_html),
            panel_cls=MDExpansionPanelOneLine(text="Produse locale")
        ))

        screen.ids.detected_problem.text = f"Problemă detectată: {class_name.capitalize()}"
        self.parentApp.root.current = "recomandation"

    def close_app(self):
        Window.close()


class SkinApp(MDApp):
    def build(self):
        self.model = load_model("model.h5")
        with open("label_encoder.pkl", "rb") as f:
            self.label_encoder = pickle.load(f)

        with open("produse/recomandari_produse.html", encoding="utf-8") as f:
            self.raw_html = f.read()

        self.title = "PowderPuff"
        self.theme_cls.theme_style = "Light"
        self.theme_cls.primary_palette = "Pink"
        self.theme_cls.primary_hue = "500"
        self.theme_cls.accent_palette = "Pink"

        Builder.load_file("main.kv")

        sm = ScreenManager()

        # Înregistrează ecranul principal
        main_screen = MainScreen(name="main")
        layout = MainLayout()
        layout.parentApp = self
        main_screen.add_widget(layout)

        sm.add_widget(main_screen)
        sm.add_widget(RecommendationScreen(name="recomandation"))

        return sm

class MainScreen(Screen):
    pass
class RecommendationScreen(Screen):
    pass
class RoutineBox(MDBoxLayout):
    def __init__(self, text="", **kwargs):
        super().__init__(**kwargs)
        self.orientation = "vertical"
        self.padding = [10, 10]
        self.spacing = 5
        self.size_hint_y = None
        self.text = text

        self.label = MDLabel(
            text=text,
            markup=True,
            size_hint_y=None,
            halign="left",
            valign="top",
            font_style="Body1"
        )

        self.label.bind(texture_size=self.adjust_height, width=self.on_width)
        self.label.bind(on_ref_press=self.open_link)
        self.add_widget(self.label)

        Clock.schedule_once(self.force_layout, 0)

    def on_width(self, instance, value):
        self.label.text_size = (value, None)

    def adjust_height(self, *args):
        self.label.height = self.label.texture_size[1]
        self.height = self.label.height + self.padding[1] * 2 + self.spacing

    def force_layout(self, *args):
        self.label.text_size = (self.label.width, None)
        self.label.texture_update()
        self.adjust_height()

    def open_link(self, instance, ref):
        import webbrowser
        webbrowser.open(ref)


if __name__ == "__main__":
    SkinApp().run()


