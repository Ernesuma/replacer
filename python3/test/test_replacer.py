#!/usr/bin/env python3

import unittest
import replacer


class Test_Replacer(unittest.TestCase):
    """
    """

    def test_get_text(self):
        """
        test the text getter
        """
        text = "Dies ist mein {mail} toller Testtext\n \< Leere Zeile\>\
<noch eine leere {Zeile}."

        myReplacer = replacer.Replacer(text, {})
        self.assertEqual(text, myReplacer.get_text())

    def test_default_filler(self):
        myReplacer = replacer.Replacer("test")
        self.assertEqual({}, myReplacer.get_filler_dict())
        self.assertEqual(0, len(myReplacer.get_filler_dict()))

    def test_get_filler_dict(self):
        test_filler_dict = {'mail': 'test.mail@address.net', 'name': "John Doe"}
        myReplacer = replacer.Replacer('test', test_filler_dict)
        self.assertEqual(test_filler_dict, myReplacer.get_filler_dict())

    def test_filled_text_plain(self):
        plain_text = "this is some test text without any stuff to replace\n/n Diese Zeile sollte mit einem 'Backslash-n' beginnen!"
        test_filler_dict = {'mail': 'test.mail@address.net', 'name': "John Doe"}
        myReplacer = replacer.Replacer(plain_text, test_filler_dict)
        self.assertEqual(plain_text, myReplacer.get_filled_text())

    def test_filled_text_easy(self):
        text = "This is my mail address: '{mail}'. My name is {name}."
        test_filler_dict = {'mail': 'test.mail@address.net', 'name': "John Doe"}
        myReplacer = replacer.Replacer(text, test_filler_dict)
        self.assertEqual("This is my mail address: 'test.mail@address.net'. My name is John Doe.",
                         myReplacer.get_filled_text())
