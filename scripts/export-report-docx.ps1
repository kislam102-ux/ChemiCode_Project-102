$ErrorActionPreference = 'Stop'

$mdPath = Join-Path (Get-Location) 'PROJECT_REPORT.md'
$docxPath = Join-Path (Get-Location) 'PROJECT_REPORT.docx'
$tempDir = Join-Path (Get-Location) '.docx_tmp'

if (-not (Test-Path $mdPath)) {
    throw "Missing input file: $mdPath"
}

if (Test-Path $tempDir) {
    Remove-Item -LiteralPath $tempDir -Recurse -Force
}

New-Item -ItemType Directory -Path $tempDir | Out-Null
New-Item -ItemType Directory -Path (Join-Path $tempDir '_rels') | Out-Null
New-Item -ItemType Directory -Path (Join-Path $tempDir 'docProps') | Out-Null
New-Item -ItemType Directory -Path (Join-Path $tempDir 'word') | Out-Null
New-Item -ItemType Directory -Path (Join-Path $tempDir 'word\_rels') | Out-Null

$lines = Get-Content $mdPath
$body = New-Object System.Collections.Generic.List[string]

foreach ($line in $lines) {
    $trim = $line.TrimEnd()

    if ([string]::IsNullOrWhiteSpace($trim)) {
        $body.Add('<w:p/>')
        continue
    }

    $style = $null
    $text = $trim

    if ($trim.StartsWith('# ')) {
        $style = 'Heading1'
        $text = $trim.Substring(2).Trim()
    } elseif ($trim.StartsWith('## ')) {
        $style = 'Heading2'
        $text = $trim.Substring(3).Trim()
    } elseif ($trim.StartsWith('### ')) {
        $style = 'Heading3'
        $text = $trim.Substring(4).Trim()
    } elseif ($trim.StartsWith('- ')) {
        $text = [char]0x2022 + ' ' + $trim.Substring(2)
    }

    $text = $text -replace '\*\*', '' -replace '`', ''
    $escaped = [System.Security.SecurityElement]::Escape($text)

    if ($style) {
        $body.Add("<w:p><w:pPr><w:pStyle w:val='$style'/></w:pPr><w:r><w:t xml:space='preserve'>$escaped</w:t></w:r></w:p>")
    } else {
        $body.Add("<w:p><w:r><w:t xml:space='preserve'>$escaped</w:t></w:r></w:p>")
    }
}

$documentXml = @"
<?xml version='1.0' encoding='UTF-8' standalone='yes'?>
<w:document xmlns:wpc='http://schemas.microsoft.com/office/word/2010/wordprocessingCanvas' xmlns:mc='http://schemas.openxmlformats.org/markup-compatibility/2006' xmlns:o='urn:schemas-microsoft-com:office:office' xmlns:r='http://schemas.openxmlformats.org/officeDocument/2006/relationships' xmlns:m='http://schemas.openxmlformats.org/officeDocument/2006/math' xmlns:v='urn:schemas-microsoft-com:vml' xmlns:wp14='http://schemas.microsoft.com/office/word/2010/wordprocessingDrawing' xmlns:wp='http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing' xmlns:w10='urn:schemas-microsoft-com:office:word' xmlns:w='http://schemas.openxmlformats.org/wordprocessingml/2006/main' xmlns:w14='http://schemas.microsoft.com/office/word/2010/wordml' xmlns:wpg='http://schemas.microsoft.com/office/word/2010/wordprocessingGroup' xmlns:wpi='http://schemas.microsoft.com/office/word/2010/wordprocessingInk' xmlns:wne='http://schemas.microsoft.com/office/word/2006/wordml' xmlns:wps='http://schemas.microsoft.com/office/word/2010/wordprocessingShape' mc:Ignorable='w14 wp14'>
  <w:body>
    $($body -join "`n    ")
    <w:sectPr>
      <w:pgSz w:w='12240' w:h='15840'/>
      <w:pgMar w:top='1440' w:right='1440' w:bottom='1440' w:left='1440' w:header='708' w:footer='708' w:gutter='0'/>
    </w:sectPr>
  </w:body>
</w:document>
"@

$stylesXml = @"
<?xml version='1.0' encoding='UTF-8' standalone='yes'?>
<w:styles xmlns:w='http://schemas.openxmlformats.org/wordprocessingml/2006/main'>
  <w:style w:type='paragraph' w:default='1' w:styleId='Normal'>
    <w:name w:val='Normal'/>
    <w:qFormat/>
    <w:rPr><w:sz w:val='24'/></w:rPr>
  </w:style>
  <w:style w:type='paragraph' w:styleId='Heading1'>
    <w:name w:val='heading 1'/>
    <w:basedOn w:val='Normal'/>
    <w:next w:val='Normal'/>
    <w:qFormat/>
    <w:rPr><w:b/><w:sz w:val='32'/></w:rPr>
  </w:style>
  <w:style w:type='paragraph' w:styleId='Heading2'>
    <w:name w:val='heading 2'/>
    <w:basedOn w:val='Normal'/>
    <w:next w:val='Normal'/>
    <w:qFormat/>
    <w:rPr><w:b/><w:sz w:val='28'/></w:rPr>
  </w:style>
  <w:style w:type='paragraph' w:styleId='Heading3'>
    <w:name w:val='heading 3'/>
    <w:basedOn w:val='Normal'/>
    <w:next w:val='Normal'/>
    <w:qFormat/>
    <w:rPr><w:b/><w:sz w:val='26'/></w:rPr>
  </w:style>
</w:styles>
"@

$contentTypesXml = @"
<?xml version='1.0' encoding='UTF-8' standalone='yes'?>
<Types xmlns='http://schemas.openxmlformats.org/package/2006/content-types'>
  <Default Extension='rels' ContentType='application/vnd.openxmlformats-package.relationships+xml'/>
  <Default Extension='xml' ContentType='application/xml'/>
  <Override PartName='/word/document.xml' ContentType='application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml'/>
  <Override PartName='/word/styles.xml' ContentType='application/vnd.openxmlformats-officedocument.wordprocessingml.styles+xml'/>
  <Override PartName='/docProps/core.xml' ContentType='application/vnd.openxmlformats-package.core-properties+xml'/>
  <Override PartName='/docProps/app.xml' ContentType='application/vnd.openxmlformats-officedocument.extended-properties+xml'/>
</Types>
"@

$rootRelsXml = @"
<?xml version='1.0' encoding='UTF-8' standalone='yes'?>
<Relationships xmlns='http://schemas.openxmlformats.org/package/2006/relationships'>
  <Relationship Id='rId1' Type='http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument' Target='word/document.xml'/>
  <Relationship Id='rId2' Type='http://schemas.openxmlformats.org/package/2006/relationships/metadata/core-properties' Target='docProps/core.xml'/>
  <Relationship Id='rId3' Type='http://schemas.openxmlformats.org/officeDocument/2006/relationships/extended-properties' Target='docProps/app.xml'/>
</Relationships>
"@

$docRelsXml = @"
<?xml version='1.0' encoding='UTF-8' standalone='yes'?>
<Relationships xmlns='http://schemas.openxmlformats.org/package/2006/relationships'>
  <Relationship Id='rId1' Type='http://schemas.openxmlformats.org/officeDocument/2006/relationships/styles' Target='styles.xml'/>
</Relationships>
"@

$coreXml = @"
<?xml version='1.0' encoding='UTF-8' standalone='yes'?>
<cp:coreProperties xmlns:cp='http://schemas.openxmlformats.org/package/2006/metadata/core-properties' xmlns:dc='http://purl.org/dc/elements/1.1/' xmlns:dcterms='http://purl.org/dc/terms/' xmlns:dcmitype='http://purl.org/dc/dcmitype/' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'>
  <dc:title>ChemiCode Project Report</dc:title>
  <dc:creator>Codex</dc:creator>
  <cp:lastModifiedBy>Codex</cp:lastModifiedBy>
  <dcterms:created xsi:type='dcterms:W3CDTF'>2026-04-05T00:00:00Z</dcterms:created>
  <dcterms:modified xsi:type='dcterms:W3CDTF'>2026-04-05T00:00:00Z</dcterms:modified>
</cp:coreProperties>
"@

$appXml = @"
<?xml version='1.0' encoding='UTF-8' standalone='yes'?>
<Properties xmlns='http://schemas.openxmlformats.org/officeDocument/2006/extended-properties' xmlns:vt='http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes'>
  <Application>Microsoft Office Word</Application>
</Properties>
"@

Set-Content -LiteralPath (Join-Path $tempDir '[Content_Types].xml') -Value $contentTypesXml -Encoding UTF8
Set-Content -LiteralPath (Join-Path $tempDir '_rels\.rels') -Value $rootRelsXml -Encoding UTF8
Set-Content -LiteralPath (Join-Path $tempDir 'docProps\core.xml') -Value $coreXml -Encoding UTF8
Set-Content -LiteralPath (Join-Path $tempDir 'docProps\app.xml') -Value $appXml -Encoding UTF8
Set-Content -LiteralPath (Join-Path $tempDir 'word\document.xml') -Value $documentXml -Encoding UTF8
Set-Content -LiteralPath (Join-Path $tempDir 'word\styles.xml') -Value $stylesXml -Encoding UTF8
Set-Content -LiteralPath (Join-Path $tempDir 'word\_rels\document.xml.rels') -Value $docRelsXml -Encoding UTF8

if (Test-Path $docxPath) {
    Remove-Item -LiteralPath $docxPath -Force
}

Add-Type -AssemblyName System.IO.Compression.FileSystem
[System.IO.Compression.ZipFile]::CreateFromDirectory($tempDir, $docxPath)
Remove-Item -LiteralPath $tempDir -Recurse -Force

Get-Item $docxPath | Select-Object Name, Length, LastWriteTime
