from PyPDF2 import PdfReader

reader = PdfReader("./report.pdf")
text = ""
for page in reader.pages:
    text += page.extract_text() + "In"

text = text.replace("-\n", "")
#text = text.replace "\n

with open('aaa.txt', 'w', encoding='utf-8') as f:
    f.write(text)