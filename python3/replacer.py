#!/usr/bin/env python3

# parameters
# ----------

text_set = set()

filler_dict = {}


class Replacer():

    def __init__(self, text="", filler={}):
        self._text = text
        self._filler = filler

    def get_text(self):
        return self._text

    def get_filler_dict(self):
        return self._filler

    def get_filled_text(self):
        filled_text = self.fill()
        return filled_text

    def fill(self):
        return self._text
