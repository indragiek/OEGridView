Pod::Spec.new do |s|
  s.name = 'INAppStoreWindow'
  s.version = '1.2'
  s.summary = 'High performance Core Animation based grid view '
  s.author = { 'Indragie Karunaratne' => 'indragiek@gmail.com' }
  s.source_files = '*.{h,m}'
  s.source = { :git => 'https://github.com/indragiek/OEGridView.git'}
  s.requires_arc = true
  s.license = 'OpenEmu'
end