import React from 'react';
import Layout from '@theme/Layout';
import Link from '@docusaurus/Link';

export default function Home() {
  return (
    <Layout
      title="Welcome to the Raytracer Documentation"
      description="Explore the documentation for the Raytracer project">
      <main style={{ textAlign: 'center', padding: '2rem' }}>
        <h1>Welcome to the Raytracer Documentation</h1>
        <p>Explore the different sections of the documentation:</p>
        <div style={{ marginTop: '2rem' }}>
          <Link to="/docs/parser" style={{ margin: '1rem', fontSize: '1.2rem' }}>
            📄 Parser
          </Link>
          <Link to="/docs/plugins" style={{ margin: '1rem', fontSize: '1.2rem' }}>
            🔌 Plugins
          </Link>
          <Link to="/docs/building" style={{ margin: '1rem', fontSize: '1.2rem' }}>
            🏗️ Building
          </Link>
          <Link to="/docs/errors" style={{ margin: '1rem', fontSize: '1.2rem' }}>
            ❗ Errors
          </Link>
        </div>
        <div style={{ marginTop: '3rem' }}>
          <a
            href="/Doc.pdf"
            target="_blank"
            rel="noopener noreferrer"
            style={{ fontSize: '1.1rem', color: '#0078e7', textDecoration: 'underline' }}
          >
            📚 View Full Doxygen PDF Documentation
          </a>
        </div>
      </main>
    </Layout>
  );
}
